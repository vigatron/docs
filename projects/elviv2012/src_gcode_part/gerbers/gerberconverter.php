<?php

// Processing Gerber File: Extended Gerber, RS-274X
// Processing Drills File: ANSI/ICP-NC-349 (Excellon defaults)


class GerberConverter {
    
    private $memfile;   // Temporary File Image
    private $type;
    private $excellon;
    private $gerber;

    public function InitFromFile($fname, $p1 = "3", $p2 = "3") {

        $this->memfile = new VHMemTxtFile();
        if ($this->memfile->LoadToMemory($fname) === false) {
            echo "Cant open file: " . $fname;
            return false;
        }

        $this->DetectFileType($this->memfile->Line(0));
        
        if($this->type == "excellon") {
            $this->excellon = new Excellon();
            $this->excellon->InitFrom($this->memfile);
        } else {
            $this->gerber = new Gerber();
            $this->gerber->InitFromFile($this->memfile, $p1, $p2);
        }

        return true;
    }
 

    public function DetectFileType($line) {
        if($line==="M48") { 
            $this->type = "excellon";
        } else {
            $this->type = "gerber";
        }
    }
   
    public function Serialize($varname) {
        if($this->type == "excellon") {
            $this->excellon->Serialize($varname);
        } else {
            $this->gerber->Serialize($varname);
        }
    }
}

