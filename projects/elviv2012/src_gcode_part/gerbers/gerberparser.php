<?php

class GerberParser {
    
    static function Split($line) {
        
        $result = Array();
        $len = strlen($line);
        
        $numtype = self::SepType($line[0]);
        $curpart = "";
        
        for($i=0;$i<$len;$i++) {
            $s = $line[$i];
            $curtype = self::SepType($s);

            if($curtype == $numtype) {
                $curpart .= $s;
            } else {
                $numtype = $curtype;
                array_push($result,$curpart);
                $curpart = $s;
            }
        }
        
        if($curpart) {
          array_push($result,$curpart);
        }
        
        return $result;
    }
    
    static function SepType($s) {
        if(is_numeric($s)) { return 1; }
        if($s==='.') { return 1; }
        if($s===',') { return 2; }
        if($s===';') { return 3; }
        if($s==='=') { return 4; }
        return 5;
    }
    
    static function INCH_TO_MM($inch) {
		 return 2.54 * $inch;
	} 
    
}
