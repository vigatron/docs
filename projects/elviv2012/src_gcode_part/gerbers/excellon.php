<?php

class Excellon {
    
    public $tools  = array();
    public $drills = array();

    public $header      = true;
    public $metric_inch = false;
    public $metric_lz   = false;

    public $act_x;
    public $act_y;
    public $act_type;
    
    const count_tools = 100;
    
    private function Reset() {
        $this->header = true;
        $this->tools = array();
        for ($i = 0; $i < self::count_tools; $i++) {
            array_push($this->tools, new ExcellonTool());
        }
        $this->drills = array();
    }

    public function InitFrom($memfile) {
        $this->Reset();
        for ($i = 0; $i < $memfile->LinesCount(); $i++) {
            $txt = $memfile->Line($i);
            $len = strlen($txt);
            if ($len < 1) { continue; }
            if(false===$this->ParseTextLine( GerberParser::Split($txt))) {
                die($txt);
            }
        }
    }
    
    // $this->ParsePercentLine(substr($line, 1, $len - 3));
    // $this->ParseStdLine(substr($line, 0, $len - 1));
    public function ParseTextLine($p) {
        return $this->header ? $this->ParseHeader($p) : $this->ParseBody($p);
    }

    
    public function ParseNewTool($p) {
        $idx = intval($p[1]);
        $this->tools[$idx]->Parse($p);
        return true;
    }
    
    public function ParseHeader($p) {
        
        if($p[0] === ';') {
            return TRUE;
        }
        
        if($p[0] === '%') {
            $this->header = false;
            return TRUE;
        } 

        if($p[0] === 'T') {
           return $this->ParseNewTool($p);
        }

        if($p[0] === 'M') {
            return $this->ParseM($p);
        }

        if($p[0] === 'INCH') {
            $this->metric_inch = true;
            if($p[2] === 'LZ') {
            $this->metric_lz   = true;
            }
            return true;
        }
        
        return false;
    }
    
    public function ParseBody($p) {
        if($p[0] === 'T') {
        return $this->ParseTool($p);
        }
        
        if(($p[0] === 'X')||($p[0] === 'Y')) {
        return $this->ParseXY($p);
        }

        if($p[0] === 'M') {
        return $this->ParseM($p);
        }
        
        return false;
    }
    
    public function ParseTool($p) {
        $this->act_type = intval($p[1]);
        return true;
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

    public function ParseXY($p) {
        
        for($i=0;$i<count($p);$i+=2) {
            if  ($p[$i]==="X")   { 
                $r = $this->ConvertCoord($p[$i+1]);
                $this->act_x  = GerberParser::INCH_TO_MM($r); }
            else if($p[$i]==="Y")   { 
                $r = $this->ConvertCoord($p[$i+1]);
                $this->act_y  = GerberParser::INCH_TO_MM($r); }
            else { return false; }
        }
        
        $drill = new ExcellonDrill();
        $drill->Set($this->act_x, $this->act_y, $this->act_type );
        array_push( $this->drills, $drill );
        return true;
    }
    
    public function ParseM($p) {
        
        // End of File
        if($p[1]==="30") {
            // var_dump($this->drills); 
        }
        
        return true;
    }

    public function Serialize($varname) {
        $bintools = $this->SerializeTools();
        $bindrills = $this->SerializeDrills();
        $result_array = array(1, $bintools, $bindrills);
        $result_serialized = VHSerializeArray($result_array);
        $result_base64 = VHEncodeBase64($result_serialized);
        B64TOJS($varname, $result_base64);
    }

    private function SerializeTools() {
        $bintools = array();
        for ($i = 0; $i < count($this->tools); $i++) {
            $tool = $this->tools[$i];
            if ($tool->IsEmpty() == false) {
            array_push($bintools, $tool->Serialize());
            }
        }
        return $bintools;
    }
    
    private function SerializeDrills() {
        $bindrills = array();
        for ($i = 0; $i < count($this->drills); $i++) {
            $route = $this->drills[$i];
            $bin = $route->Serialize();
            array_push($bindrills, $bin);
        }
        return $bindrills;
    }
    
}
