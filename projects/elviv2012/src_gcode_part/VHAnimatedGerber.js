function VHAnimatedGerber() {
	
}

// .divid = DIV for insertion
// .

VHAnimatedGerber.prototype.Init = function(p) {
	
	// Create canvas
	var parent = '#'+p.divid;
	var elementID = 'canvas' + $('canvas').length; // Unique ID

	$('<canvas>').attr({ id: elementID }).css({
	    width: 		$('#'+p.divid).width() - 2  + 'px', // rectWidth +
	    height:  	$('#'+p.divid).height() - 2 + 'px', // rectHeight +
	    border:  '2px solid #DDD'
	}).appendTo(parent);

	$('<div>').attr({
		'id' : 		"AnimatedGerberTMP",
		'style' :	"display: none"
	}).appendTo(parent);

	// var canvas = document.getElementById(elementID); // Use the created element	
	
	// Temporary:
	// Gerber List ID : 15,16, 17,18
	// -------------------------
	//		Board #1 <TOP>,<GTO>
	//		Board #2 <TOP>,<GTO>
	
	//	Gerber Content 1
	//	Gerber Content 2
	
}

