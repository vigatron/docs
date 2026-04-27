<?php

class ExcellonDrill {
    
    public $x,$y,$t;
    
    public function Set($x,$y,$t) {
        $this->x = $x;
        $this->y = $y;
        $this->t = $t;
    }
    
    public function Serialize() {
        return array($this->x,$this->y,$this->t);
    }
}
