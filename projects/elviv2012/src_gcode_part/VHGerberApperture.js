// ---------------------------------------
// Gerber Apperture
// ---------------------------------------
function VHGerberApperture() { this.type = 0; this.v1 = 0; this.v2 = 0; }
VHGerberApperture.prototype.typec = 1; // circle
VHGerberApperture.prototype.typer = 2; // rectangle
VHGerberApperture.prototype.typeo = 3; // oval
VHGerberApperture.prototype.typep = 4; // octagon
VHGerberApperture.prototype.typet = 5; // thermal

VHGerberApperture.prototype.IsEmpty = function() { return (!this.type) ? true : false; };
VHGerberApperture.prototype.SetCircle = function(cls, r) { this.cls = cls; this.type = this.typec; this.v1 = r; };
VHGerberApperture.prototype.SetRectangle = function(cls, w, h) { this.cls = cls; this.type = this.typer; this.v1 = w; this.v2 = h; };
VHGerberApperture.prototype.SetOval = function(cls, w, h) { this.cls = cls; this.type = this.typeo; this.v1 = w; this.v2 = h; };
VHGerberApperture.prototype.SetPolygon = function(cls, r, sides, deg) { this.cls = cls; this.type = this.typep; this.r = r; this.sides = sides; this.deg = deg; };
VHGerberApperture.prototype.SetThermal = function(cls, tno) { this.cls = cls; this.type = this.typet; this.thn = tno; }

VHGerberApperture.prototype.IsCircle = function()       { return (this.type == 1) ? true : false; };
VHGerberApperture.prototype.IsRectangle = function()    { return (this.type == 2) ? true : false; };
VHGerberApperture.prototype.IsOval = function()         { return (this.type == 3) ? true : false; };
VHGerberApperture.prototype.IsPolygon = function()      { return (this.type == 4) ? true : false; };
VHGerberApperture.prototype.IsThermal = function()      { return (this.type == 5) ? true : false; };

VHGerberApperture.prototype.InitFromArray = function(app) {
    var type = app[0]; var cls = app[1];
    if(type===this.typec)    { this.SetCircle(cls, app[2]); return true; }
    if(type===this.typer)    { this.SetRectangle(cls,app[2],app[3]); return true; }
    if(type===this.typeo)    { this.SetOval(cls,app[2],app[3]); return true; }
    if(type===this.typep)    { this.SetPolygon(cls,app[2],app[3],app[4]); return true;}
    if(type===this.typet)    { this.SetThermal(cls,app[2]); return true; }
    console.log(this);
    JSDef.Abort("Unknown apperture");
    return false;
};

VHGerberApperture.prototype.Debug = function() { console.log("*Apperture ", this); };


