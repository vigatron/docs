<?php

class VHGerberFormatDetector {

    const type_unknown = 0;
    const type_gerber = 1;
    const type_excellon = 2;
    
    private $type;
    private $gp;
    
    function __construct($textlines) {
    	$this->gp = new VHGerberTools();
    	$this->type = $this->Detect($textlines);
    }
    
    public function Detect($textlines) {
        if($this->TryGerber($textlines)) { return self::type_gerber; }
        if($this->TryExcellon($textlines)) { return self::type_excellon; }
        return self::type_unknown;
    }
    
    public function TypeGerber() { return self::type_gerber == $this->type; }
    
    public function TypeExcellon() { return self::type_excellon == $this->type; }
        
    private function TryGerber($textlines) {
        $line = $textlines[0];
        // $hdr = $this->gp->Split($memfile->Line(0));
        // if($hdr[1]==="FSLAX") { return TRUE; }
        if(substr($line, -1)==="%") { return true; }
        if(substr($line, -1)==="*") { return true; }
        return FALSE;
    }
    
    private function TryExcellon($textlines) {
        $hdr = $this->gp->Split($textlines[0]);
        if($hdr[0]==="M") { return TRUE; }
        return FALSE;
    }
}

