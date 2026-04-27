<?php

class VHGerberXYPointer {

    private $x,$y,$i,$j;
    private $updated;
    private $extended;
    
    public function __construct() { $this->updated = false; $this->x = 0; $this->y = 0; $this->i=0; $this->j=0; }
    
    public function IsUpdated() { return $this->updated; }
    public function IsExtended() { return $this->extended; }
    
    public function ClearUpdatedFlag() { $this->updated = false; $this->extended = false; }
    
    public function UpdateX($x) { $this->x = $x; $this->updated = true; }
    public function UpdateY($y) { $this->y = $y; $this->updated = true; }
    public function UpdateI($i) { $this->i = $i; $this->extended = true; }
    public function UpdateJ($j) { $this->j = $j; $this->extended = true; }
    
    public function GetX() { return $this->x; }
    public function GetY() { return $this->y; }
    public function GetI() { return $this->i; }
    public function GetJ() { return $this->j; }
}
