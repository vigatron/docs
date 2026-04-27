<?php

class VHGerberPolygon {
    
    private $arr = array();
    
    private $fill;

    public function AddPoint($x,$y) { $this->arr[] = array($x,$y); }
    
    public function SetFill($flag) { $this->fill = $flag; }
    
    public function GetFill() { return $this->fill; }
    
    public function PointsCount() { return count($this->arr); }
    
    public function Debug() {
        GerberInfoOut("Polygon data>");
        $cnt = count($this->arr);
        for($i=0;$i<$cnt;$i++) { $point = $this->arr[$i]; GerberInfoOut("{$point[0]}:{$point[1]}"); }
    }
    
    public function Serialize() {
        $r = array();
        for($i=0;$i<count($this->arr);$i++) { $r[]= $this->arr[$i]; }
        $r[]=$this->fill;
        return $r;
    }
    
}
