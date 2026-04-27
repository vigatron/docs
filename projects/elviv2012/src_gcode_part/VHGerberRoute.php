<?php

class VHGerberRoute {
	
    private $cls;
    private $arr = array();

    public function AddPoint($x, $y) { $this->arr[]= array($x, $y); }
    
    public function AddArc($x,$y,$cx,$cy,$dir) { $this->arr[]=array($x,$y,$cx,$cy,$dir); }
    
    public function PointsCount() { return count($this->arr); }
    
    public function SetClass($cls) { $this->cls = $cls; }

    public function Debug() {
        if($this->cls) { GerberInfoOut("* Route, App #{$this->cls}>"); } else { /* die("Warn1!"); */ }
    
        $cnt = count($this->arr);
        for($i=0;$i<$cnt;$i++) { 
            echo "  "; $point = $this->arr[$i]; echo "{$point[0]}:{$point[1]}";
            if(count($point)>2) { echo " - arc {$point[2]}:{$point[3]} / {$point[4]}"; }
        }
        GerberInfoOut("");
    }

    public function Serialize() {
        // if ($cnt < 2) { die("GerberRoute Serialization failed!"); } $cnt -=1; $result = array($this->arr[0]);
        // $cnt = count($this->arr);
        // for ($i = 0; $i < $cnt; $i++) { $pnt = $this->arr[1 + $i]; array_push($result, $pnt[0], $pnt[1]); }
        return array($this->cls, $this->arr);
    }
    
}

