<?php

// C=1,R=2,O=3
class VHGerberApperture {

    public $type;
    public $cls;
    public $v1,$v2,$v3,$v4;

    const typee = 0;
    const typec = 1;
    const typer = 2;
    const typeo = 3;
    const typep = 4;
    const typet = 5; //Thermal

    public function __construct() { $this->type = self::typee; }

    public function GetType() { return $this->type; }

    public function IsEmpty() { return ($this->type == self::typee) ? true : false; }

    public function Serialize() {
        $res = array();
        $res[]=$this->type;
        $res[]=$this->cls;
        $res[]=$this->v1;
        if($this->v2) { $res[]=$this->v2; }
        if($this->v3) { $res[]=$this->v3; }
        if($this->v4) { $res[]=$this->v4; }
        return $res;
    }

    public function DebugPair($pairs) { for($i=0;$i<count($pairs);$i++) { $p = $pairs[$i]; TextLine("#{$i} - {$p[0]} - {$p[1]}"); } }
    
    private function ParseAppFloatInt($txt,$afterComma) {
        $f = floatval($txt)*(pow(10,$afterComma));
        return intval($f);
    }
    
    public function Parse($pairs,$afterComma)
    {
        $this->cls = intval($pairs[1][1]);
        $fig = $pairs[2][1];
        
        // Thermal Pad parsing
        if($fig==="THERM") { 
            $this->type = self::typet;
            $this->v1 = intval($pairs[3][1]);
            return TRUE;
    	}
        
        $this->v1 = $this->ParseAppFloatInt($pairs[4][1], $afterComma);
        
        if(count($pairs) >= 6) {    $this->v2 = $fig==="P" ? intval($pairs[6][1])  		: $this->ParseAppFloatInt($pairs[6][1],  $afterComma); }
        if(count($pairs) >= 8) {    $this->v3 = $fig==="P" ? floatval($pairs[8][1])  	: $this->ParseAppFloatInt($pairs[8][1],  $afterComma); }
        if(count($pairs) >= 10) {   $this->v4 = $fig==="P" ? $pairs[10][1] 				: $this->ParseAppFloatInt($pairs[10][1], $afterComma); }
        if($fig=="C") { $this->type = self::typec; return TRUE; }
        if($fig=="R") { $this->type = self::typer; return TRUE; }
        if($fig=="P") { $this->type = self::typep; return TRUE; }
        if($fig=="O") { $this->type = self::typeo; return TRUE; }
        $this->DebugPair($pairs);
        return FALSE;
    }
    
    public function Debug() { GerberInfoOut("{$this->cls} {$this->type} | {$this->v1},{$this->v2},{$this->v3},{$this->v4}"); }
}

