<?php

class ExcellonTool {
    
    public $idx;
    public $f;
    public $s;
    public $c;
    public $valid = false;
    
    public function Parse($p) {
        for($i=0;$i<count($p);$i+=2) {
            if($p[$i]==="T")        { $this->idx    = intval($p[$i+1]); }
            else if($p[$i]==="F")   { $this->f      = $p[$i+1]; }
            else if($p[$i]==="S")   { $this->s      = $p[$i+1]; }
            else if($p[$i]==="C")   { $this->c      = GerberParser::INCH_TO_MM(floatval($p[$i+1]))*50; }
            else { return false; }
        }
        $this->valid = true;
        return true;
    }
    
    public function IsEmpty() {
        return $this->valid ? false : true;
    }
    
    public function Serialize() {
        return array( $this->idx, $this->f, $this->s, $this->c );
    }
}
