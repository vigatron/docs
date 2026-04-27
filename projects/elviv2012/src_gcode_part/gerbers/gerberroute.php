<?php

class GerberRoute {
	
    public $arr = array();

    public function __construct($cls) {
        array_push($this->arr, $cls);
    }

    public function AddPoint($x, $y) {
        array_push($this->arr, array($x, $y));
    }

    public function Serialize() {
        $cnt = count($this->arr);
        if ($cnt < 2) { die("GerberRoute Serialization failed!"); }
        $cnt -=1;
        $result = array($this->arr[0]);
        for ($i = 0; $i < $cnt; $i++) {
            $pnt = $this->arr[1 + $i];
            array_push($result, $pnt[0], $pnt[1]);
        }
        return $result;
    }

}
