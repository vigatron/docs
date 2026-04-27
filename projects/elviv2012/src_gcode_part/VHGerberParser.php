<?php

function GerberInfoOut($t) { echo $t.'<br>'; }

class VHGerberParser
{
	
	public  $apps       = array();
	public  $routes     = array();
	private $polygons   = array();
	private $thermals   = array();
	
	private $route;
	private $polygon;
	
	// private $cur_x, $cur_y, $cur_i, $cur_j;
	public  $xypointer;
	private $cur_d;
	private $cur_class;
	private $objFormat;
	
	// Pointer mode
	const interpolation_linear = 1;
	const interpolation_circular_clockwise = 2;
	const interpolation_circular_counterwise = 3;
	private $interpolation;
	
	// Arc parameters
	const quadrant_single = 1;
	const quadrant_multi = 2;
	private $quadrant;
	
	private $polygon_mode = FALSE;
	
	// Polygon Polarity runtime option
	const polarity_set = 1;
	const polarity_clear = 2;
	private $polarity;
	
	//
	const image_polarity_pos = 1;
	const image_polarity_neg = 2;
	private $image_polarity;
	
	// excellon part
	private $excellon_header;
	private $excellon_act_type;
	
	public  $tools      = array();
	public  $drills     = array();
	
	public $descriptors;
	
	private $fd; // Format detector
	
	
	public function __construct() {
	
		$this->objFormat = new VHGerberFormat();
		$this->xypointer = new VHGerberXYPointer();
	
		$this->descriptors = array();
		$this->DescriptorReset();
		
		$this->route 	= new VHGerberRoute();
		$this->polygon	= new VHGerberPolygon();
		
		$this->image_polarity = self::image_polarity_pos;
	}
	
	public function InitFromText($textlines) {
		
		$this->fd = new VHGerberFormatDetector($textlines);
		
		if($this->fd->TypeGerber()) { return $this->ParseGerberFromText($textlines); }
		else
		if($this->fd->TypeExcellon()) { return $this->ParseExcellonFromText($textlines); }
		
		GerberInfoOut("Unknown input file format");
		return FALSE;
	}
	
	private function ParseGerberFromText($textlines) {
	
		for ($i = 0; $i < count($textlines); $i++) {
			if( FALSE == $this->ParseLine($textlines[$i])) { return FALSE; }
		}
		// self::Debug();
		return TRUE;
	}
	
	private function Debug()
	{
		// $memfile->Debug();
		$this->DEBUG_apps();
		$this->DEBUG_routes();
		$this->DEBUG_polygons();
	}
	
	private function ParseLine($line)
	{
		$linetype = VHGerberTools::DetectLineType($line);
		
		// VHPrint::Line($linetype. ' - '. $line);
		
		if($linetype == VHGerberTools::linetype_wstar) { return $this->ParseGerberTextLineWStar($line,$linetype); }
		if($linetype == VHGerberTools::linetype_unknown) { $this->STOP($line); return false; }
		if($linetype == VHGerberTools::linetype_plain) { $this->STOP($line); return false; }
		if($linetype == VHGerberTools::linetype_empty ) { $this->DescriptorAdd(); return true; }
		if($linetype == VHGerberTools::linetype_wstar_and_procent ) { return $this->ParseLineWProcentsStar($line,$linetype); }
		
		$this->STOP($line);
		return FALSE;
	}
	
	private function STOP($txt) { die(" Halt on ParseGerberTextLine: ".$txt); }
	
	private function ParseLineWProcentsStar($line,$linetype) {
		$linecontent = VHGerberTools::GetLineContent($line, $linetype);
		if($this->PreParse($linecontent) == TRUE) { return TRUE; }
		$arr = VHGerberTools::ParseParameters($linecontent);
		if( false == $this->ParseObject($arr,$linetype) ) { die("Parser internal error :".$line); }
		return true;
	}
	
	private function CheckPrefix($line,$prefix) {
		$llen = strlen($line); $plen = strlen($prefix);
		if($plen>$llen) { return FALSE; }
		$source = substr($line,0,$plen);
		return (strcmp($source,$prefix) == 0) ? TRUE : FALSE;
	}
	
	private function PreParse($line) {
		if($this->CheckPrefix($line, "IPPOS"))  { $this->image_polarity = self::image_polarity_pos ; return TRUE; }
		if($this->CheckPrefix($line, "IPNEG"))  { $this->image_polarity = self::image_polarity_neg ; return TRUE; }
		if($this->CheckPrefix($line, "LN"))     { return TRUE; } // Layer name ( comment )
		if($this->CheckPrefix($line, "FS"))  	{ return $this->objFormat->ParseFS(substr($line,2)); }
		if($this->CheckPrefix($line, "MO"))  	{ return $this->objFormat->ParseMO(substr($line,2)); }
		if($this->CheckPrefix($line, "LPC")) 	{ $this->polarity = self::polarity_clear; return TRUE; }
		if($this->CheckPrefix($line, "LPD")) 	{ $this->polarity = self::polarity_set; return TRUE; }
		if($this->CheckPrefix($line, "G04")) 	{ $this->DescriptorAppendText("Comment"); return TRUE; }
		return FALSE;
	}
	

	// echo "* {$dsc} ".count($this->descriptors);
	function DescriptorReset() { $this->cur_desc = " ; "; }
	function DescriptorAdd() { $this->descriptors[] = $this->cur_desc; $this->DescriptorReset();  }
	function DescriptorAppendText($txt) { /* $this->cur_desc .= $txt; */ }
	function GetDescriptorLine($i) { return $this->descriptors[$i]; }
	function GetDescriptorLines() { return count($this->descriptors); }
	
	
	private function InitExcellon($memfile) {
		// TextLine("Parsing Excellon");
		$this->excellon_header = true;
		for ($i = 0; $i < $memfile->LinesCount(); $i++) {
			$txt = $memfile->Line($i); if (strlen($txt) < 1) { continue; }
			if( FALSE == $this->ParseExcellonTextLine($txt)) { GerberError("Cant parse! ", $txt); return FALSE; }
		}
		// $this->DEBUG_tools(); $this->DEBUG_drills();
		return TRUE;
	}
	
	private function ParseExcellonTextLine($line) {
		$content = GerberTools::Split($line);
		return $this->excellon_header ? $this->ParseExcellonHeader($content) : $this->ParseExcellonBody($content);
	}
	
	public function ParseExcellonHeader($p) {
		if($p[0] === ';') { return $this->ParseExcellonHeaderComment($p); }
		if($p[0] === '%') { $this->excellon_header = false; return TRUE; }
		if($p[0] === 'T') { $tool = new ExcellonTool(); $tool->Parse($p); array_push($this->tools,$tool); return true; }
		if($p[0] === 'M') { return $this->ParseExcellonM($p); }
		if($p[0] === 'INCH') { $this->objFormat->SetMetric(GerberFormat::metric_inch); /* if($p[2] === 'LZ') { $this->metric_lz = true; } */ return true; }
		GerberError(__LINE__, "PFX ".$p[0]);
		return false;
	}
	
	public function ParseExcellonHeaderComment($p) {
		if($p[1]==="FILE_FORMAT") { $this->objFormat->AssignFromExcellon( intval($p[3]), intval($p[5]) ); return true; }
		if($p[1]==="Layer_Color") { return true;}
		if($p[1]==="TYPE") { return true;}
		return false;
	}
	
	public function ParseExcellonBody($p) {
		if($p[0] === 'T') { $this->excellon_act_type = intval($p[1]); return true; }
		if(($p[0] === 'X')||($p[0] === 'Y')) { return $this->ParseExcellonXY($p); }
		if($p[0] === 'M') { return $this->ParseExcellonM($p); }
		GerberError(__LINE__, $p);
		return false;
	}
	
	private function tmp($p) {
		$l = strlen($p); $za = 7 - $l; $r = $p;
		for($i=0;$i<$za;$i++) { $r.= "0"; }
		return $r;
	}
	
	public function ParseExcellonXY($p) {
		// $act_x = 0; $act_y = 0;
		for($i=0;$i<count($p);$i+=2) {
			if  ($p[$i]==="X")      { $this->xypointer->UpdateX(intval($this->tmp($p[$i+1]))); }
			else if($p[$i]==="Y")   { $this->xypointer->UpdateY(intval($this->tmp($p[$i+1]))); }
			else { return false; }
		}
	
		$drill = new ExcellonDrill();
		$drill->Set($this->xypointer->GetX(), $this->xypointer->GetY(), $this->excellon_act_type );
		array_push( $this->drills, $drill );
		return true;
	}
	
	public function ParseExcellonM($p) {
		// var_dump($this->drills);
		if($p[1]==="30") { } // End of File
		return true;
	}
	
	public function GetFormatObject() { return $this->objFormat; }
	
	public function GetAppertures()
	{
		return $this->apps;
	}
	
	public function GetRoutes() { return $this->routes; }
	public function GetPolygons() { return $this->polygons; }
	
	private function ParseGerberTextLineWStar($line,$linetype) {
		 
		$cnt = substr_count($line,'*');
	
		// Multi-mode
		if($cnt>1) { 
			$lines = explode("*",$line); // var_dump($lines);
			for($i=0;$i<count($lines);$i++) {
				$line = $lines[$i];
				if($line!=="") {
					$r = $this->ParseGerberTextLineWStar($lines[$i]."*", $linetype);
					if($r == false) { return false; }
				}
			}
			return true;
		}
	
		// TextLine("ParseGerberTextLineWStar: ".$line);
	
		// Single mode
		$linecontent = VHGerberTools::GetLineContent($line, $linetype);
		if($this->PreParse($linecontent) == TRUE) { return TRUE; }
		$arr = VHGerberTools::ParseParameters($linecontent);
		if( false == $this->ParseObject($arr,$linetype) ) { die("Parser internal error :".$line); }
		return true;
	}
	
	private function ParseObject($arr,$type) {
	
		$result = true;
		$cnt = count($arr);
		$firstword = $arr[0][1];
		$this->cur_d = 0;
		
		if($cnt < 1) { $this->warn("Something wrong: "); var_dump($arr); return TRUE; }
		if($firstword==="ADD")  { return $this->AddApperture($arr); }
		if($firstword==="AMTHERM") { return $this->AddThermal($arr); }
		if($firstword==="M") { $this->AddRoute(); return TRUE; }
		$this->cur_d = 0;
	
		// Parse Line Parameters
		for($i=0;$i<$cnt;$i+=2) { if( $this->ParsePair($arr[$i][1],$arr[$i+1][1]) ) { continue; } return FALSE; }
	
		if($this->cur_d >=10 ) { // D>=10 used for routes only
			$this->AddRoute();
			$this->cur_class = $this->cur_d;
			$result = true;
			$this->DescriptorAppendText(" Using apperture #".$this->cur_d);
		} else if($this->cur_d > 0) {
			$result = $this->polygon_mode ? $this->ProcessPolygon() : $this->ProcessRoute();
		}
	
		$this->xypointer->ClearUpdatedFlag();
		return $result;
	}
	
	private function ParsePair($pfx,$val) {      // TextLine("Parse Pair ".$pfx." = ".$val);
		if($pfx==="G") { return $this->ParseG($val); }
		if($pfx==="X") { $this->DescriptorAppendText(" Set X to {$val}"); $this->xypointer->UpdateX( $this->objFormat->value($val) ); return TRUE; }
		if($pfx==="Y") { $this->DescriptorAppendText(" Set Y to {$val}"); $this->xypointer->UpdateY( $this->objFormat->value($val) ); return TRUE; }
		if($pfx==="D") { $this->cur_d = intval($val); return TRUE; }
		if($pfx==="I") { $this->xypointer->UpdateI( $this->objFormat->value($val) ); return TRUE; }
		if($pfx==="J") { $this->xypointer->UpdateJ( $this->objFormat->value($val) ); return TRUE; }
		return FALSE;
	}
	
	private function AddRoute() {
	
		$pcnt = $this->route->PointsCount();
		// TextLine("Add Route called");
		if($pcnt>0) {
			$this->route->SetClass($this->cur_class);
			$this->routes[]= $this->route; /* $this->route->Debug(); */
			// GerberInfo("Added route - "); var_dump($this->route);
			$this->route = new VHGerberRoute();
		} else { /* GerberInfo("Warning, attempt to add empty route!"); */ }
	}
	
	private function ExtendPath() {
		
		if($this->interpolation == self::interpolation_linear )
		{  
			$this->route->AddPoint($this->xypointer->GetX(),$this->xypointer->GetY());
		}
		else {
			
			$this->route->AddArc(
					$this->xypointer->GetX(),
					$this->xypointer->GetY(),
					$this->xypointer->GetI(),
					$this->xypointer->GetJ(),
					$this->interpolation );
		}
	}
	
	private function ProcessRoute() {
		// TextLine("ProcessRoute cur_d=".$this->cur_d);
		if($this->cur_d==1)         {
			$this->ExtendPath();
			return TRUE;
		} // Store point
		else if($this->cur_d==2)    {
			$this->AddRoute();
			$this->ExtendPath();
			return TRUE;
		} // Move to point
		else
			if($this->cur_d==3)    {
			$this->route = new VHGerberRoute();
			$this->ExtendPath();
			$this->route->SetClass($this->cur_class);
			$this->routes[]= $this->route;
			return TRUE;
		} // FLASH
		
		return FALSE;
	}
	
	private function ProcessPolygon() {
		if($this->cur_d==1) { }
		else if($this->cur_d==2) {
			if($this->polygon->PointsCount()>1) { $this->polygon->SetFill($this->polarity); $this->polygons[]= $this->polygon; }
			$this->polygon = new VHGerberPolygon(); // Starting new
		} else { die("WTF2!"); }
		$this->polygon->AddPoint($this->xypointer->GetX(),$this->xypointer->GetY());
		return TRUE;
	}
	
	private function ParseG($val) {
		if($val=="70") { $this->DescriptorAppendText(" Using INCH metric system"); $this->objFormat->SetMetric(VHGerberFormat::metric_inch); return TRUE; }
		if($val=="71") { $this->DescriptorAppendText(" Using MM metric system"); $this->objFormat->SetMetric(VHGerberFormat::metric_mm); return TRUE; }
		if($val=="1" ) { $this->DescriptorAppendText(" Set Linear interpolation"); $this->interpolation = self::interpolation_linear; return TRUE; }
		if($val=="2" ) { $this->DescriptorAppendText("Circular interpolation clockwise"); $this->interpolation = self::interpolation_circular_clockwise; return TRUE; }
		if($val=="3" ) { $this->DescriptorAppendText("Circular interpolation counter-clockwise"); $this->interpolation = self::interpolation_circular_counterwise; return TRUE; }
		if($val=="74") { $this->DescriptorAppendText("Arcs drawing mode / single-quadrant"); $this->quadrant = self::quadrant_single; return TRUE; }
		if($val=="75") { $this->DescriptorAppendText("Arcs drawing mode / multi-quadrant"); $this->quadrant = self::quadrant_multi; return TRUE; }
		if($val=="36") { $this->polygon_mode = TRUE; return TRUE;}
		if($val=="37") { $this->polygon_mode = FALSE; return TRUE; }
		if($val=="54") { return TRUE; } // Precedes an apperture selection D-Code, no effect, deprecated
	
		return FALSE;
	}
	
	private function AddApperture($pairs) {
		$app = new VHGerberApperture();
		if( FALSE == $app->Parse($pairs,$this->objFormat->GetAfterCommaX())) { return FALSE; }
		$this->apps[] = $app;
		return TRUE;
	}
		
	private function AddThermal($pairs) {
		$thrm = new VHGerberThermal();
		if( FALSE == $thrm->Parse($pairs)) { return FALSE; }
		$this->thermals[] = $thrm;
		return TRUE;
	}
	
	public function DEBUG_apps() {
		$cnt = count($this->apps);
		GerberInfoOut("--- Appertures: {$cnt}");
		for ($i = 0; $i < count($this->apps); $i++) { $app = $this->apps[$i]; $app->Debug(); }
	}
	
	public function DEBUG_routes() {
		$cnt = count($this->routes);
		GerberInfoOut("--- Routes count: {$cnt}");
		for ($i = 0; $i < $cnt; $i++) { $route = $this->routes[$i]; $route->Debug(); }
	}
	
	public function DEBUG_polygons() { 
		$cnt = count($this->polygons);
		GerberInfoOut("--- Polygons count: {$cnt}");
		for($i=0;$i<$cnt;$i++) {  $polygon = $this->polygons[$i]; $polygon->Debug(); }
	}
	
	public function DEBUG_tools() {
		$cnt = count($this->tools);
		GerberInfo("--- Tools count: {$cnt}");
		for ($i = 0; $i < $cnt; $i++) { $tool = $this->tools[$i]; $tool->Debug(); }
	}
	
	public function DEBUG_drills() {
		$cnt = count($this->drills);
		GerberInfo("--- Drills count: {$cnt}");
		for ($i = 0; $i < $cnt; $i++) { $drill = $this->drills[$i]; $drill->Debug(); }
	}
	
	function warn($t) { echo __CLASS__."Warning: ".$t; }

	
	// ---------------------------------------------------------------------------------
	//    private $nr,$gap,$width,$finger;
	public function SerializeAutomatic() {
		if($this->fd->TypeGerber())   { return VHBase64::Encode(self::SerializeGerberToArray()); }
		if($this->fd->TypeExcellon()) { return VHBase64::Encode(self::SerializeExcellonToArray()); }
		GerberError(__LINE__, "Serialization of unsupported format!");
		return false;
	}
	
	private function SerializeGerberToArray() {
		// var_dump($this->apps);
		// var_dump($this->routes);
		// $this->DEBUG_routes();
		return VHSerialize::SerializeArray( array("VHGRB1.11",
			$this->GetFormatObject()->Serialize(), // $bin_format,
			self::SerializeAppertures($this->GetAppertures()), // $bin_apps,
			self::SerializeRoutes($this->GetRoutes()), // $bin_traces,
			self::SerializePolygons($this->GetPolygons()) /* $bin_polygons */ ));
	}
	
	private function SerializeExcellonToArray() {
		return VHSerialize::SerializeArray( array("VHEXCELLON-1.1",
				$this->GetFormatObject()->Serialize(),
				self::SerializeTools($exc->tools),
				self::SerializeDrills($exc->drills)));
	}
	
	private function SerializeAppertures($AppsArray) {
		$bin_apps = array(); for ($i = 0; $i < count($AppsArray); $i++) {
			if ($AppsArray[$i]->IsEmpty() == false) { $bin_apps[]= $AppsArray[$i]->Serialize(); }
		}
		return $bin_apps;
	}
	
	private function SerializeRoutes($RoutesArray) {
		$bin_traces = array(); for ($i = 0; $i < count($RoutesArray); $i++) { $bin_traces[]= $RoutesArray[$i]->Serialize(); } return $bin_traces;
	}
	
	private function SerializePolygons($PolygonsArray) {
		$bin_polygons = array(); for ($i = 0; $i < count($PolygonsArray); $i++) { $bin_polygons[]= $PolygonsArray[$i]->Serialize(); } return $bin_polygons;
	}
	
	private function SerializeTools($ToolsArray) {
		$bintools = array(); for ($i = 0; $i < count($ToolsArray); $i++) {
			if($ToolsArray[$i]->IsEmpty() == false ) { $bintools[]= $ToolsArray[$i]->Serialize(); }
		}
		return $bintools;
	}
	
	private function SerializeDrills($DrillsArray) {
		$bindrills = array(); for ($i = 0; $i < count($DrillsArray); $i++) { $bindrills[]= $DrillsArray[$i]= $DrillsArray->Serialize(); } return $bindrills;
	}
	
	public function SerializeAsPlainText($grb) {
		if($grb->fd->TypeGerber())     { return $this->SerializeGerberToArray(); }
		if($grb->fd->TypeExcellon() )  { return $this->SerializeExcellonToArray(); }
		GerberError(__LINE__, "Serialization of unsupported format!");
		return false;
	}
	
	
}


/*
 class Excellon {

 public $header      = true;
 public $metric_inch = false;
 public $metric_lz   = false;

 public $act_x; public $act_y; public $act_type;

 private function Reset() {
 $this->header = true;
 $this->tools = array();
 for ($i = 0; $i < self::count_tools; $i++) {  }
 $this->drills = array();
 }

 private function ConvertCoord($val) {

 $p1 = substr($val, 0, 2);
 $p2 = substr($val, 2);
 $result = floatval($p1);
 // echo $val." - ".$p1." - ".$p2."<br>";
 $restlen = strlen($p2);
 $result += floatval($p2)/pow(10,$restlen);
 return $result*100;
 }

 }
 */

