<?php

// ---------------------------------------------
// Init From
// ---------------------------------------------
// Option #1 Content, Text / VHMemTxtFile
// Option #2 Gerber File / Precompiled
// Option #3 From ZipFile : gerber / Precompiled
// Option #4 By ID ?

class VHGerberFile {
	
	// private $memfile;
	// private $memfiletype;		// Gerber, excellon, vhgrb, vhexcellon
	// private $memfilepacked;
	
	private $textcontent;
	private $fileObject;
	
	public function LoadByID($id)
	{
		$sqlo = VHSQL::Instance();
		$this->fileObject = $sqlo->select_by_id('gerberfiles', $id);
		
		$file = $_SERVER['DOCUMENT_ROOT'].$this->fileObject['filepath'].$this->fileObject['filename'];
		$fhandle = fopen($file, "r");
		
		$this->textcontent = array();
		
		if ($fhandle != FALSE) {
			while (!feof($fhandle)) {
				$line = trim(preg_replace('/\s\s+/', ' ', fgets($fhandle)));
				array_push($this->textcontent, $line); // VHPrint::Line($line);
			}
			
			fclose($fhandle);
			return TRUE;
		}
		
		return FALSE;
	}
	
	public function GetProps($id) {
		$sqlo = VHSQL::Instance();
		$this->fileObject = $sqlo->select_by_id('gerberfiles', $id);
		return $this->fileObject;
	}
	
	public function TextContent() {
		return $this->textcontent;
	}
	
	// Paths & locations
	/*
	private function LocalPath() { return filter_input(INPUT_SERVER, 'DOCUMENT_ROOT'). "/db"; }
	private function LocalPath_PublicGerbers() { return $this->LocalPath()."/PublicGerbers"; }

	private function LoadFromZIP() {
		$zippath  = $_SERVER['DOCUMENT_ROOT'].$this->PublicGerberFilesFolder()."/".$this->ArchiveName();
		$filebin  = VHSTD::ReadFileFromZIP($zippath,$this->FileName());
		return $filebin;
	}

	private function LoadFromFolder() {
		$filepath = $_SERVER['DOCUMENT_ROOT']."/db/".$this->FileName();
		$memfile = new VHMemTxtFile();
		if($memfile->LoadToMemory($filepath) == false ) { return false; }
		return $memfile->Content();
	}

	public function LoadContent() {
		$content = $this->IsPacked() ? $this->LoadFromZIP() : $this->LoadFromFolder();
		return $content;
	}

	public function LoadCompiledContent() {
		$content = $this->IsPacked() ? $this->LoadFromZIP() : $this->LoadFromFolder();

		$arr = explode("\n",$content);
		$memfile = new VHMemTxtFile();
		$memfile->InitFromArray($arr);

		$grb = new Gerber();
		$grb->InitFromFile($memfile);
		return GerberSerializator::SerializeAutomatic($grb);
	}

	public function IconFile() {

		$fullfile = "";
		$fname    = "";

		// Icon for packed file located in folder <zipname> / filename.png
		if($this->IsPacked()) {
			$file = $this->file['arch']; // $pinfo = pathinfo($file);
			$folder = substr($this->ArchiveName(), 0, -4); // basename($file); //
			$fname = $this->PublicGerberFilesFolder()."/".$folder."/".$this->file['filename'].".png";
			$fullfile = $_SERVER['DOCUMENT_ROOT'].$fname;
		} else {
			$fname = "/db".$this->FileName().".png";
			$fullfile = $_SERVER['DOCUMENT_ROOT'].$fname;
		}

		return file_exists($fullfile) ? $fname : false;
	}

	public function UploadNewIcon($dataurl)
	{
		$image = base64_decode(explode(',',$dataurl)[1]);

		$dir = "";
		$file = "";

		if($this->IsPacked()) {

			$zipfolder = substr($this->ArchiveName(), 0, -4);

			$dir = $_SERVER['DOCUMENT_ROOT'].$this->PublicGerberFilesFolder()."/".$zipfolder."/";
			if (!file_exists($dir)) { mkdir($dir, 0777); }
			$file = $dir.$this->FileName().".png";
			// return "The directory $dir was successfully created.";
		} else {

			$file = $_SERVER['DOCUMENT_ROOT']."/db".$this->FileName().".png";
			// return "Unpacked gerber file";
		}

		$f = fopen($file, 'w');
		fwrite($f,$image);
		fclose($f);

		return true;
	}
	*/

	/*
		public function LoadGerberPre() {
		$zipfile = $_SERVER['DOCUMENT_ROOT'].$this->file['arch'];
		$getname = $this->file['filename'].".pre";
		$bincontent = VHSTD::ReadFileFromZIP($zipfile,$getname);
		// var_dump($this,$zipfile,$getname,$bincontent);
		return $bincontent;
		}
	*/

}
