<?php

class VHGerberTools {
    
    //
	const sym_numeric = 1;
    const sym_text = 2;
    const sym_separator = 3;
    
    //
    const linetype_unknown = 0;
    const linetype_plain = 1;
    const linetype_wstar = 2;
    const linetype_procent = 3;
    const linetype_wstar_and_procent = 4;
    const linetype_empty = 5;
    
    //
    const undef = 0;
    const numeric = 1;
    const coma = 2;
    const pcoma = 3;
    const eq = 4;
    const prc = 5;
    
    static function GERBER_abc_code($sym) {
        $num = array( ".", "-","+" );
        if (is_numeric($sym)) { return self::sym_numeric; }
        for($i=0;$i<count($num);$i++) { if($num[$i]===$sym) { return self::sym_numeric; } }
        if ($sym == ',') { return self::sym_separator; }
        return self::sym_text;
    }

    // ||($lastsym)  // + ($lastsym?1:0) // if ($i == ($len - 1)) { }
    static function ParseParameters($txt) {
        $result = array(); $len  = strlen($txt);
        if($len<1) { return GerberErr::err_emptyString; }

        $wordo = 0; $wordl = 1; $wordt = self::GERBER_abc_code($txt[0]); // runtime
        
        for ($i = 1; $i < $len; $i++) {
            $runtype = self::GERBER_abc_code($txt[$i]);
            if($runtype!=$wordt) {
                array_push($result,array($wordt,substr($txt,$wordo,$wordl)));
                $wordt = $runtype; $wordo = $i; $wordl = 1; 
            } else { $wordl++; }
        }

        array_push($result, array($wordt,substr($txt,$wordo,$wordl)));
        
        return $result;
    }
    
    static function DetectLineType($txt) {
        $len = strlen($txt); $lenm1 = $len-1; $lenm2 = $len - 2;
        if($len < 1) { return self::linetype_empty; }
        if($len < 3) { return self::linetype_unknown; }
        if($txt[$lenm1] === '*') { return self::linetype_wstar; }
        if(($txt[0] === "%")&&($txt[$lenm1] === "%")) {  if($txt[$lenm2]==="*") { return self::linetype_wstar_and_procent;} return self::linetype_procent; }
        return self::linetype_plain;
    }
    
    static function GetLineContent($txt,$type) {
        $len = strlen($txt);
        switch($type) {
            case self::linetype_plain:   return $txt;
            case self::linetype_wstar:   return substr($txt, 0, $len - 1);
            case self::linetype_procent: return substr($txt, 1, $len - 2);
            case self::linetype_wstar_and_procent: return substr($txt, 1, $len - 3);
            default: { return ""; }
        }
    }
    
    static function Split($line) {
        $result = Array();
        $len = strlen($line);
        $numtype = self::SepType($line[0]);
        $curpart = "";
        
        for($i=0;$i<$len;$i++) { $s = $line[$i]; $curtype = self::SepType($s);
            if($curtype == $numtype) { $curpart .= $s; } else { $numtype = $curtype; array_push($result,$curpart); $curpart = $s; } }
        if($curpart) { array_push($result,$curpart); }
        return $result;
    }
    
    static function SepType($s) {
        if(is_numeric($s)) { return self::numeric; }
        if($s==='.') { return self::numeric; }
        if($s===',') { return self::coma; }
        if($s===';') { return self::pcoma; }
        if($s==='=') { return self::eq; }
        if($s==='%') { return self::prc; }
        return self::undef;
    }

    static function INCH_TO_MM($inch) {
        return 2.54 * $inch;
    }
    
    static function IsMultiStar($txt) {
        return false;
    }
    
    static function SplitStars($str) {
        return array();
    }
}
