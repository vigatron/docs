<?php

class Gerber {

    private $dim1, $dim2;
    private $param_inch = 0;
    private $param_inpoly = 0;
    
    public $apps    = array();
    public $routes  = array();
    private $route;
    
    private $cur_x;
    private $cur_y;
    private $cur_d;

    const count_apps = 300;
    
    private function InitAppertures() {
        for ($i = 0; $i < self::count_apps; $i++) {
            array_push($this->apps, new GerberApperture());
        }
    }

    public function __construct() {

        $this->dim1 = 3;
        $this->dim2 = 3;
        $this->cur_x = 0;
        $this->cur_y = 0;
        $this->cur_d = 0;
        $this->InitAppertures();
        $this->route = new GerberRoute(0);
    }

    public function InitFromFile($memfile, $p1 = "3", $p2 = "3") {
        $this->dim1 = $p1;
        $this->dim2 = $p2;

        for ($i = 0; $i < $memfile->LinesCount(); $i++) {
            $txt = $memfile->Line($i);
            if (strlen($txt) < 1) {
                continue;
            }
            $this->ParseTextLine($txt);
        }
    }

    public function DEBUG_apps() {
        for ($i = 0; $i < self::count_apps; $i++) {
            $app = $this->apps[$i];
                if ($app->type != GerberApperture::typee) {
                echo($i);
                var_dump($app);
                echo "<br>";
                }
            }
        }

    public function DEBUG_routes() {
        for ($i = 0; $i < count($this->routes); $i++) {
            $r = $this->routes[$i]->arr;
            for ($z = 1; $z < count($r); $z++) {
                echo "[{$r[$z][0]}:{$r[$z][1]}] ";
            } echo "<br>";
        }
        echo "<br>";
    }

    public function ParseTextLine($line) {

        $len = strlen($line);
        if ($len < 3) {
            return FALSE;
        }

        if ($line[0] == '%') {
            $this->ParsePercentLine(substr($line, 1, $len - 3));
        } else if ($line[$len - 1] == '*') {
            $this->ParseStdLine(substr($line, 0, $len - 1));
        } else {
            warn("no % no *");
        }

        return TRUE;
    }

    private function ParsePercentLine($txt) {

        $params = $this->ParseCommentedParameters($txt);

        if (count($params) < 1) {
            $this->warn("Something wrong: " . $txt);
            return 2;
        }

        $param = $params[0][1];

        if ($param == "FSLAX") {
            return 0;
        }
        if ($param == "MOIN") {
            $this->param_inch = 1;
            return 0;
        }
        if ($param == "ADD") {
            if (!$this->AddApperture($params)) {
            return 0; }
        }
        
        if ($param == "LPC") {
            return 0;
        } // TODO: Clear polarity
        
        if ($param == "LPD") {
            return 0;
        } // TODO: new level dark polarity
        echo "SpecialLine (?): " . $txt . "<br>";

        return 1;
    }

    private function AddApperture($params) {
        $cls = intval($params[1][1]);
        $type = $params[2][1];

        if ($type == "R") {
            $dim1 = ($this->param_inch == 1) ? GerberParser::INCH_TO_MM((float) $params[4][1]) : ((float) $params[4][1]);
            $dim2 = ($this->param_inch == 1) ? GerberParser::INCH_TO_MM((float) $params[6][1]) : ((float) $params[6][1]);
            $app = $this->apps[$cls];
            $app->Rect($cls, $dim1, $dim2); // * 8 * 8
            return 0;
        } else if ($type == "O") {
            $dim1 = ($this->param_inch == 1) ? GerberParser::INCH_TO_MM((float) $params[4][1]) : ((float) $params[4][1]);
            $dim2 = ($this->param_inch == 1) ? GerberParser::INCH_TO_MM((float) $params[6][1]) : ((float) $params[6][1]);
            $app = $this->apps[$cls];
            $app->Oval($cls, $dim1, $dim2);
            return 0;
        } else if ($type == "C") {
            $dim1 = ($this->param_inch == 1) ? GerberParser::INCH_TO_MM((float) $params[4][1]) : ((float) $params[4][1]);
            $app = $this->apps[$cls];
            $app->Circle($cls, $dim1); //  * 2.57
            return 0;
        } else {
            $this->warn("Wrong apperture");
        }

        return 1;
    }

    // TODO: Interpolation Mode
    // TODO: Multi-Quadrant
    private function Parse_GCode($values) {
        // if(count($values)>2) $this->warn("G !");

        $val = intval($values[1][1]);
        if ($val == 1) {
            return 0;
        }
        if ($val == 36) {
            if ($this->param_inpoly == 1) {
                die("Already in open polygon");
            }
            $this->param_inpoly = 1;
            return 0;
        }
        if ($val == 37) {
            if ($this->param_inpoly != 1) {
                die("Cant close polygon ..");
            } $this->param_inpoly = 0;
            return 0;
        }
        if ($val == 70) {
            $this->param_inch = 1;
            return 0;
        }
        if ($val == 71) {
            $this->param_inch = 0;
            return 0;
        }
        if ($val == 75) {
            return 0;
        }

        return 1;
    }

    private function OpenPath($cls) {
        $this->route = new GerberRoute($cls);
    }

    private function AddPath($x, $y) {
        $this->route->AddPoint($x, $y);
    }

    private function ClosePath() {
        if (count($this->route->arr) > 1) {
            $this->routes[] = $this->route;
        }
    }

    private function Parse_XYDCode($values) {
        
        // echo " :: "; var_dump($values); echo "<br>";

        $tmp_d = 0;
        $p_i = "";
        $p_j = "";

        // parsing XYZIJ variables 
        for ($i = 0; $i < count($values); $i+=2) {
            $pfx = $values[$i][1];
            $val = $this->TextToFloat($values[$i + 1][1]);
            if ($pfx === "X") { $this->cur_x = ($this->param_inch==1) ? GerberParser::INCH_TO_MM($val) : $val; }
            if ($pfx === "Y") { $this->cur_y = ($this->param_inch==1) ? GerberParser::INCH_TO_MM($val) : $val; }
            if ($pfx === "D") { $tmp_d = intval($values[$i + 1][1]); }
            if ($pfx === "I") { $p_i = $val; }
            if ($pfx === "J") { $p_j = $val; }
        }
        
        // Parse D-Codes
        if ($tmp_d == 0) { die("WTF"); }
        if ($tmp_d == 1) { $this->AddPath($this->cur_x, $this->cur_y); return 0; }
        if ($tmp_d == 2) { $this->ClosePath(); $this->OpenPath($this->cur_d); $this->AddPath($this->cur_x, $this->cur_y); return 0; }
        if ($tmp_d == 3) { $this->ClosePath(); return 0; }
        if ($tmp_d >  3) { $this->ClosePath(); $this->cur_d = $tmp_d; return 0; }
        
        return 1;
    }

    private function ParseStdLine($txt) {

        $params = $this->ParseCommentedParameters($txt);

        if (count($params) < 1) {
            $this->warn("Something wrong: " . $txt);
            return 2;
        }

        $param = $params[0][1];

        if ($param == "G") {
            return $this->Parse_GCode($params);
        }
        if (($param == "X") || ($param == 'Y') || ($param == 'D')) {
            return $this->Parse_XYDCode($params);
        }
        if ($param == "M") {
            $this->ClosePath();
            return 0;
        }

        echo "StdLine (?): " . $txt . "<br>";
        return 1;
    }

    private function ParseCommentedParameters($txt) {
        $result = array();
        $len = strlen($txt);
        $paramo = 0;
        $paramt = -1;

        for ($i = 0; $i < $len; $i++) {

            $sym = $txt[$i];

            if ($i == 0) {
                $paramt = $this->GERBER_abc_code($sym);
            }

            $curtype = $this->GERBER_abc_code($sym);

            if ($curtype != $paramt) {
                array_push($result, array($paramt, substr($txt, $paramo, $i - $paramo)));
                $paramt = $curtype;
                $paramo = $i;
            } else if ($i == ($len - 1)) {
                array_push($result, array($paramt, substr($txt, $paramo, $i + 1 - $paramo)));
            }
        }

        return $result;
    }

    function GERBER_abc_code($sym) {
		if(is_numeric($sym)) return 1;
		if($sym=='.') return 1;
		if($sym=='-') return 1;
		if($sym=='+') return 1;
		if($sym==',') return 3;
		return 2;
	}

	public function GetArray() {
	 	$gerber_all = array($gerber_types, $gerber_array);
	 	return $gerber_all;
	}
	
	public function TextToFloat($txt) {
		$sgn = 0;
		$src = $txt;
		if(($txt[0]=='-')||($txt[0]=='+')) { $src = substr($txt,1,strlen($txt)-1); }
		if($txt[0]=='-') $sgn=1;
		while(strlen($src)<($this->dim1+$this->dim2)) { $src="0".$src; }
		$part1  = floatval(substr($src,0,$this->dim1));
		$part2  = floatval(substr($src,$this->dim1,$this->dim2))/(pow(10,$this->dim2));
		$val = $part1 + $part2;
                if($sgn) { $val *= -1; }
		// echo "Converting {$txt} = {$val}<br>\n";
		return $val;
	}
	
	function warn($t) {
		echo __CLASS__."Warning: ".$t;
	}

	public function Serialize($varname) {
        $bin_apps = $this->SerializeAppertures();
        $bin_traces = $this->SerializeRoutes();
        $result_serialized = VHSerializeArray(array(2, $bin_apps, $bin_traces));
        $result_base64 = VHEncodeBase64($result_serialized);
        B64TOJS($varname, $result_base64);
        }

        private function SerializeAppertures() {
        $bin_apps = array();
        for ($i = 0; $i < count($this->apps); $i++) {
            $app = $this->apps[$i];
            if ($app->IsEmpty() == false) {
                $bin = $app->Serialize();
                array_push($bin_apps, $bin);
            }
        }
        return $bin_apps;
        }

        private function SerializeRoutes() {
        $bin_traces = array();
        for ($i = 0; $i < count($this->routes); $i++) {
            $route = $this->routes[$i]; // var_dump($route); echo "<br><br>";
            $bin = $route->Serialize(); // var_dump($bin); echo "<br>";
            array_push($bin_traces, $bin);
        }
        return $bin_traces;
        }

}

