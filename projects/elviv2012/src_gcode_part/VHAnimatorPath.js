function VHPathAnimator2D()
{ 
	
}

// p.from_x
// p.from_y
// p.to_x
// p.to_y
// p.type = Linear / Sin / Cos

VHPathAnimator2D.prototype.Setup = function(p) { 
	this.p = p;
}

VHPathAnimator2D.prototype.GetPos = function(percent) {
	
	return { x: 0, y: 0 };
}
