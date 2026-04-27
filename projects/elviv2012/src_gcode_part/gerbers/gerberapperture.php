<?php

// C=1,R=2,O=3
class GerberApperture {

    public $type;
    public $cls;
    public $v1;
    public $v2;

    const typee = 0;
    const typec = 1;
    const typer = 2;
    const typeo = 3;

    public function __construct() {
        $this->type = self::typee;
    }

    public function Circle($cls, $r) {
        $this->type = self::typec;
        $this->cls = $cls;
        $this->v1 = $r;
    }

    public function Rect($cls, $w, $h) {
        $this->type = self::typer;
        $this->cls = $cls;
        $this->v1 = $w;
        $this->v2 = $h;
    }

    public function Oval($cls, $w, $h) {
        $this->type = self::typeo;
        $this->cls = $cls;
        $this->v1 = $w;
        $this->v2 = $h;
    }

    public function GetType() {
        return $type;
    }

    public function IsEmpty() {
        return ($this->type == self::typee) ? true : false;
    }

    public function Serialize() {
        if ($this->type == self::typee) {
            return array(0);
        } else if ($this->type == self::typec) {
            return array(1, $this->cls, $this->v1);
        } else if ($this->type == self::typer) {
            return array(2, $this->cls, $this->v1, $this->v2);
        } else if ($this->type == self::typeo) {
            return array(3, $this->cls, $this->v1, $this->v2);
        } else {
            die("apperture serialize");
        }
    }

}
