<?php

require_once '../../vhplatform.php';

$p1 = intval(VHParams::SafeGET("fileid"));

$gFile = new VHGerberFile();
$props = $gFile->GetProps($p1);


$name 	= pathinfo($props['name'], PATHINFO_FILENAME );
$ext  	= pathinfo($props['name'], PATHINFO_EXTENSION );
$ext_d 	= "Top Layer";


function Param($fld, $val)
{
	return VHDIV::OutputDIVC('GerberInfoLine',
			VHDIV::OutputDIVC('GerberInfoField', $fld) . VHDIV::OutputDIVC('GerberInfoValue', $val )
	);
}


echo VHDIV::OutputDIVC('GerberInfoText',$name);
echo '<br>';

echo Param("Extension", 	$ext . ', ' . $ext_d );
echo Param("File Size", 	$props['filesize']. " Bytes" ); 
echo Param("Published by", 	$props['author']);
echo Param("Date/Time",		$props['cdatetime']);
echo Param("MD5", 			$props['md5']);

echo VHDIV::ClearBoth();
