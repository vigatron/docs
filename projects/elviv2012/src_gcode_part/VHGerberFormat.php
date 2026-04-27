<?php

class VHGerberFormat {
    
    const type1_lz = 1;
    const type1_tz = 2;
    const type1_ex = 3;
    
    const type2_abs = 1;
    const type2_inc = 2;
    
    const metric_inch = 1;
    const metric_mm = 2;
    
    private $type1;
    private $type2;
    
    private $xdim1,$xdim2;
    private $ydim1,$ydim2;
    
    private $var_metric; // File metric
    
    public function __construct()
    {
    	$this->xdim1=0;
    	$this->xdim2=0;
    	$this->ydim1=0;
    	$this->ydim2=0;
    	$this->type1=0;
    	$this->type2=0;
    	$this->var_metric=0;
    }
    
    public function Serialize() {
    	return array( $this->var_metric, $this->xdim1, $this->xdim2, $this->ydim1, $this->ydim2 );
    }
    
    private function ParseTypes($line) {
        if($line[0]=="L") { $this->type1 = self::type1_lz; }
        if($line[0]=="T") { $this->type1 = self::type1_tz; }
        if($line[0]=="D") { $this->type1 = self::type1_ex; }
        if($line[1]=="A") { $this->type2 = self::type2_abs; }
        if($line[1]=="I") { $this->type2 = self::type2_inc; }        
    }
    
    private function ParseValues($parsed) {
        for($i=0;$i<count($parsed);$i+=2) { 
            $pair1 = $parsed[$i];$txt = $pair1[1]; $pair2 = $parsed[$i+1];$val = $pair2[1];
            if($txt=="X") { $this->xdim1 = intval($val[0]); $this->xdim2 = intval($val[1]); }
            else if($txt=="Y")  { $this->ydim1 = intval($val[0]); $this->ydim2 = intval($val[1]); }
            else { return FALSE; } 
        }
    }
     
    public function ParseFS($line) { // GerberInfoOut("Init format from: {$line}");
        $this->ParseTypes($line);
        $parsed = VHGerberTools::ParseParameters(substr($line,2));
        $this->ParseValues($parsed);
        return $this->FinalCheck();
    }
    
    public function ParseMO($line) {
        if($line === "IN") { $this->var_metric = self::metric_inch; return TRUE; }
        if($line === "MM") { $this->var_metric = self::metric_mm; return TRUE; }
        return FALSE;
    }
    
    public function AssignFromExcellon($v1,$v2) {
         $this->xdim1 = $v1; $this->xdim2 = $v2; $this->ydim1 = $v1; $this->ydim2 = $v2;
    }
    
    public function SetMetric($m) { $this->var_metric = $m; }
    
    public function GetAfterCommaX() { return $this->xdim2; }
    
    private function FinalCheck() {
        if(!$this->type1) { return FALSE; }
        if(!$this->type2) { return FALSE; }
        if(!$this->xdim1) { return FALSE; }
        if(!$this->xdim2) { return FALSE; }
        if(!$this->ydim1) { return FALSE; }
        if(!$this->ydim2) { return FALSE; }
        return TRUE;
    }
    
    public function value($txt) {
        return intval($txt);
    }
}

