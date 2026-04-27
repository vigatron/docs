/* ------------------------------------------------------------------------ */
function ComplexColor(color,alpha,solidFill) { this.color = color; this.alpha = alpha; this.fill = solidFill; }
ComplexColor.prototype.Color = function() { return this.color; };
ComplexColor.prototype.Alpha = function() { return this.alpha; };
ComplexColor.prototype.Solid = function() { return this.fill; };
