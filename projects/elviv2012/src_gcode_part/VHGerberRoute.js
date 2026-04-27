// ---------------------------------------
// Gerber Route
// ---------------------------------------
function VHGerberRoute(cls) {
    this.path = new Array();
    this.cls = cls;
}

VHGerberRoute.prototype.ClockWise = 3;
VHGerberRoute.prototype.InitFromArray = function(routes) { for(var i=0;i<routes.length;i++) { this.path.push(routes[i]); } };
VHGerberRoute.prototype.Add = function(x, y) { this.path.push(new Array(x, y)); };
VHGerberRoute.prototype.Area = function() {

    if(!this.path.length) {  return { x_min : 0, y_min: 0, x_max: 0, y_max: 0 }; }

    var x_min = this.path[0][0];
    var y_min = this.path[0][1];
    var x_max = this.path[0][0];
    var y_max = this.path[0][1];

    for(var i=1;i<this.path.length;i++) {
        var x =  this.path[i][0];
        var y =  this.path[i][1];
        if (x < x_min) { x_min = x; } 
        if (y < y_min) { y_min = y; }
        if (x > x_max) { x_max = x; }
        if (y > y_max) { y_max = y; }
    }
    
    return { x_min : x_min, y_min: y_min, x_max: x_max, y_max: y_max };
};

VHGerberRoute.prototype.Debug = function() {
    var txt="";
    for(var i=0;i<this.path.length;i++) {
        var p = this.path[i];
        if(p.length<=2) { txt += " ["+p[0]+":"+p[1]+"]"; }
        else { txt += " ["+p[0]+":"+p[1]+ " via " + p[2] + ":" + p[3] + "*" + p[4]+"]"; }
    }
    // console.log("Route.Debug :",txt);
};
