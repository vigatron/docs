
function VHGerberView() {
	this.vhcanvas = new VHCanvas();
}

VHGerberView.prototype.const_inch   = 1;
VHGerberView.prototype.const_mm     = 2;

// params.canvas_fin
// params.w
// params.h

VHGerberView.prototype.Setup = function(params) {
    
    this.colorSchemes = new VHGerberColorsSchemes();
    this.colorScheme = this.colorSchemes.Get(0);

    var fin_canvas = document.getElementById(params.canvas);
    var w = fin_canvas.width;
    var h = fin_canvas.height;
    this.vhcanvas.InitOffscreen({ name: 'offs', width: w, height: h }); // InitFromObject(this.canvas);
    this.ctx = this.vhcanvas.ctx;
    this.ShowInUnits = this.const_mm;
    this.mk = 1;
    this.params = params;
};

//TODO: Fix resize offscreen
VHGerberView.prototype.Resize = function() {  
    var fin_canvas = document.getElementById(this.params.canvas);
    JSDef.ResizeCanvasObj(this.vhcanvas.canvas, fin_canvas.width, fin_canvas.height );
    this.ctx = this.vhcanvas.ctx; // getContext("2d");
};

    // this.offscr = CreateOffscreenCanvas( { name: 'offscr', width: 400, height: 400 });
    // console.log(this.offscr);
    // var ctx = this.offscr.getContext('2d');
    // console.log(ctx);
   
    // var vhcnv = new VHCanvas();
    // vhcnv.InitOffscreen({ name: 'offs', width: 400, height: 400 });
    // vhcnv.Circle( new VHPoint2D(100,100),10);
    // 
    
    // var canvas = document.getElementById(params.canvas);
    // this.ctx = canvas.getContext("2d");
    // this.canvas = canvas;
    // this.gerberColors.Setup( { filetypes: this.pcb.filestype } );
    // this.sysColors = this.gerberColors.GetSystemColors(0,0);

VHGerberView.prototype.DisplayedInInch = function() { return this.ShowInUnits === this.const_inch; };

VHGerberView.prototype.DisplayedInMm = function()   { return this.ShowInUnits === this.const_mm; };

VHGerberView.prototype.CalcXMMYMM = function(mouseX, mouseY) {
    var dx = mouseX - this.screen_x; var dy = this.screen_y - mouseY;
    return { xmm : (dx / this.zoom_x / 10), ymm : (dy / this.zoom_y / 10) };
};

VHGerberView.prototype.CalcXYUnits = function(mouseX,mouseY,format) { };

VHGerberView.prototype.ZoomedX = function(val) { return (this.screen_x + (val*this.zoom_x)); };
VHGerberView.prototype.ZoomedY = function(val) { return (this.screen_y - (val*this.zoom_y)); };

VHGerberView.prototype.ZoomIn = function(mouse_x,mouse_y) {
    var xymm = this.CalcXMMYMM(mouse_x,mouse_y); // point to scale
    var k = 1.1;
    if (this.zoom_x < 10000) { this.zoom_x *= k; this.zoom_y *= k; }
    this.screen_x = mouse_x - (xymm.xmm*10*this.zoom_x);
    this.screen_y = mouse_y + (xymm.ymm*10*this.zoom_y);
};

VHGerberView.prototype.ZoomOut = function(mouse_x,mouse_y) {
    var xymm = this.CalcXMMYMM(mouse_x,mouse_y); // point to scale
    var k = 1.1;
    if (this.zoom_x > 0.0001) { this.zoom_x /= k; this.zoom_y /= k; }
    this.screen_x = mouse_x - (xymm.xmm*10*this.zoom_x);
    this.screen_y = mouse_y + (xymm.ymm*10*this.zoom_y);
};

VHGerberView.prototype.MoveX = function(dx) { this.screen_x += dx; };
VHGerberView.prototype.MoveY = function(dy) { this.screen_y += dy; };

// [routes]

// -------------------------------------------------
// Function: 
// -------------------------------------------------
//  .elements   [route1,route2, ... route3]
//  .gerber     []
//  .rate       [0..50..100]
VHGerberView.prototype.AutoZoom = function(params) {
    
    if( params.gerber ) {
        var area = params.area;
        var w = this.vhcanvas.Width();
        var h = this.vhcanvas.Height();
        var k1 = area.w / w;
        var k2 = area.h / h;
        var l = (k1>k2) ? w : h;
        var areal = (l/100) * params.rate;
        var zoom_k = (k1>k2) ? (areal/area.w) : (areal/area.h);
        this.zoom_x = zoom_k;
        this.zoom_y = zoom_k;
    }
    // console.log("exit AutoZoom", this);
};

VHGerberView.prototype.Centering = function(params) {
        
    if( params.gerber ) {
        var area = params.gerber.Area(); // console.log("centering area:",area);
        this.screen_x  = this.vhcanvas.Width()/2;
        this.screen_y  = this.vhcanvas.Height()/2;
        this.screen_x -= this.zoom_x * ( area.x_min + (area.w/2));
        this.screen_y += this.zoom_y * ( area.y_min + (area.h/2));
    }
    // console.log("exit Centering", this);
};

VHGerberView.prototype.CenteringBoard = function(params) {
    var gerber = params.gerber;
    var gerberarea = gerber.Area();
    this.AutoZoom( { gerber: gerber, area: gerberarea, rate: params.rate } );
    this.Centering( { gerber: gerber, area: gerberarea } );
};

VHGerberView.prototype.ClearScreen = function() {
    
    this.ctx.beginPath();
    this.ctx.strokeStyle = "#900000";
    this.ctx.fillStyle = this.colorScheme.sysColors.background;
    this.ctx.lineWidth = 1.0;
    this.ctx.rect(0, 0, this.vhcanvas.Width(),this.vhcanvas.Height());
    this.ctx.fill();
    this.ctx.stroke();
    this.ctx.closePath();
};

VHGerberView.prototype.DrawGrid = function(format) {
  
    this.ctx.strokeStyle = this.colorScheme.sysColors.grid;
    this.ctx.lineWidth=1;
    
    var step = this.DisplayedInInch() ? format.UnitsInInch() : format.UnitsInCm();
    
    var w = this.vhcanvas.Width();
    var h = this.vhcanvas.Height();
    
    var xf = parseInt(Math.floor( (0 - this.screen_x)/(this.zoom_x*step)))*step;
    var xt = parseInt(Math.floor( (w - this.screen_x)/(this.zoom_x*step)))*step;
    var yf = parseInt(Math.floor( (this.screen_y - h)/(this.zoom_y*step)))*step;
    var yt = parseInt(Math.floor( (this.screen_y)/(this.zoom_y*step)))*step;

    for(q=xf;q<=xt;q+=step) {
        var pf = new VHPoint2D(this.ZoomedX(q),0);
        var pt = new VHPoint2D(this.ZoomedX(q),h);
        this.vhcanvas.SharpLine(pf,pt);
    }

    for(q=yf;q<=yt;q+=step) {
        var pf = new VHPoint2D(0,this.ZoomedY(q));
        var pt = new VHPoint2D(w,this.ZoomedY(q));
        this.vhcanvas.SharpLine(pf,pt);
    }
    
};

VHGerberView.prototype.DrawOrigin = function() {

  var l = 10000;
    
  this.ctx.strokeStyle="rgb(0,155,0)";
  this.ctx.lineWidth=1000*this.zoom_x;

  this.ctx.beginPath();
  this.ctx.moveTo( this.ZoomedX((-1)*l) , this.ZoomedY((-1)*l) );
  this.ctx.lineTo( this.ZoomedX((+1)*l) , this.ZoomedY((+1)*l) );
  this.ctx.stroke();
  this.ctx.moveTo( this.ZoomedX((+1)*l) , this.ZoomedY((-1)*l) );
  this.ctx.lineTo( this.ZoomedX((-1)*l) , this.ZoomedY((+1)*l) );
  this.ctx.stroke();
  this.ctx.closePath();
};

VHGerberView.prototype.DrawDrill = function(excellon,drill,tool,color) {
    
    var radius = (tool.c/2) * this.zoom_x * 100000; // console.log(radius,tool,drill);
    
    this.ctx.strokeStyle    = color; // "#C00"; // this.colorScheme.Color(idx); // "#00C000";
    this.ctx.fillStyle      = color;
    this.ctx.lineWidth      = 0.2; // * this.zoom_x;
    
    this.ctx.beginPath();
    this.ctx.arc( this.ZoomedX(drill.x), this.ZoomedY(drill.y), radius, 0, 2 * Math.PI, false);
    this.ctx.stroke();
    this.ctx.fill();
    this.ctx.closePath();
    
};

VHGerberView.prototype.DrawRoute = function(gerber,route,apperture,color) {
    
    this.ctx.strokeStyle    = color;
    this.ctx.fillStyle      = color;

    try {
    if      (apperture.type === apperture.typec)    { this.DrawRouteTypeC(route,apperture); return; }
    else if (apperture.type === apperture.typer)    { this.DrawRouteTypeR(route,apperture); return; }
    else if (apperture.type === apperture.typeo)    { this.DrawRouteTypeO(route,apperture); return; }
    else if (apperture.type === apperture.typep)    { this.DrawRouteTypeP(route,apperture); return; }
    } catch(err) {
        // console.log(route,apperture);
        // console.log(err);
        console.log("catch!");
    }
  
    console.log("Unknown Apperture: ", apperture);
    console.log("Current route Apperture: ", route);
    abort();
};

VHGerberView.prototype.DrawRouteTypeC = function(route,apperture) { 
    
    // route.Debug();
    
    var path = route.path; 

    this.vhcanvas.SetW(apperture.v1 * this.zoom_x); // * this.mk
        
    for (var z = 1; z < path.length; z++) {

        var x = path[z][0];
        var y = path[z][1];
        var x_old = path[z - 1][0];
        var y_old = path[z - 1][1];

        var pf = new VHPoint2D(this.ZoomedX(x_old),this.ZoomedY(y_old));
        var pt = new VHPoint2D(this.ZoomedX(x),this.ZoomedY(y));
        
        var p = path[z];
        if(p.length<3) {
            this.vhcanvas.Line(pf, pt);
        } else {
            var cx = x_old + p[2];
            var cy = y_old + p[3];
            var dx = cx - p[0];
            var dy = cy - p[1];
            var r = Math.sqrt((dx*dx)+(dy*dy));
            // console.log(cx,cy,r); console.log(x_old,y_old); console.log(x,y);
            var pc = new VHPoint2D(this.ZoomedX(cx),this.ZoomedY(cy));
            var dir = p[4] !== path.ClockWise ? true : false;
            // this.vhcanvas.Circle(pc,5);
            this.vhcanvas.Arc(pc,r * this.zoom_x,pf,pt,dir);
        }
    }

    // Draw middle points
    this.ctx.lineWidth = 0.01;

    for (var i = 0; i < path.length; i++) {
        var radius = apperture.v1 * this.zoom_x / 2; // * this.mk
        this.ctx.beginPath();
        this.ctx.arc(this.ZoomedX(path[i][0]), this.ZoomedY(path[i][1]), radius, 0, 2 * Math.PI, false);
        this.ctx.stroke();
        this.ctx.fill();
        this.ctx.closePath();
    }
        // if(path.length==1) { console.log(path);}
};

VHGerberView.prototype.DrawRouteTypeR = function(route,apperture) {
        
    var path = route.path;
    if (path.length > 1) { console.log(route,apperture); JSDef.Abort("??? Warn :( !!"); }

    var w = apperture.v1 * this.mk;
    var h = apperture.v2 * this.mk;
    var x = this.ZoomedX(path[0][0] - (w / 2));
    var y = this.ZoomedY(path[0][1] + (h / 2));

    // this.ctx.strokeStyle="rgb(200,0,0)";
    // this.ctx.fillStyle="rgb(200,0,0)";
    var pc = new VHPoint2D(x,y);
    this.vhcanvas.SetW(0.01);
    this.vhcanvas.Rect(pc, w * this.zoom_x, h * this.zoom_y);
    
};

VHGerberView.prototype.DrawRouteTypeO = function(route,apperture) {
    var path = route.path;
    if (path.length > 1) { JSDef.Abort("Warn !!"); }

    var w = apperture.v1 * this.mk;
    var h = apperture.v2 * this.mk;
    var x = this.ZoomedX(path[0][0] - (w / 2));
    var y = this.ZoomedY(path[0][1] + (h / 2));
    var pc = new VHPoint2D(x,y);
    this.vhcanvas.SetW(0.01);
    this.vhcanvas.RectO(pc,w*this.zoom_x,h*this.zoom_y);
};

VHGerberView.prototype.DrawRouteTypeP = function(route,apperture) {
    var path = route.path;
    var x = this.ZoomedX(path[0][0]);
    var y = this.ZoomedY(path[0][1]);
    var r = apperture.r * this.zoom_x * this.mk / 2;
    var sides  = apperture.sides;
    var astep = Math.PI * 2 / sides;
    var sa = apperture.deg * Math.PI * 2 / 360;
    var pc = new VHPoint2D(x,y);
    var pts = new VHPoint2DArr();
    for(var i=0;i<sides;i++) { var pt = new VHPoint2D(pc.x + (r*Math.sin(sa+(i*astep))),pc.y + (r*Math.cos(sa+(i*astep)))); pts.Add(pt); }
    // this.vhcanvas.
    this.vhcanvas.Poly(pts);
};

/*
VHGerberView.prototype.DrawRouteSLine = function() { };
VHGerberView.prototype.DrawRouteArc = function() { };
*/

VHGerberView.prototype.DrawPolygon = function(gerber,polygon,color) {
    
    var cnt = polygon.length; var cntl = cnt-1;

    this.ctx.strokeStyle    = color;
    this.ctx.lineWidth      = 1;

    this.ctx.beginPath();
    this.ctx.moveTo(this.ZoomedX(polygon[0][0]),this.ZoomedY(polygon[0][1]) );
    for(var i=1;i<(cntl);i++) { this.ctx.lineTo(this.ZoomedX(polygon[i][0]),this.ZoomedY(polygon[i][1]) ); }
    this.ctx.closePath();
    
    this.ctx.fillStyle = (polygon[cntl]<2) ? color : "rgb(0,0,0)";
    this.ctx.fill(); this.ctx.stroke();
};

VHGerberView.prototype.DrawKeepout = function(gerber,grbtype) {

    var colorObj = this.colorScheme.GetLayerColor(grbtype);
    this.ctx.lineWidth = this.zoom_x;

    if(typeof colorObj !== 'string') {
        var color = colorObj.color;
        var fill  = colorObj.fill;
        var points = gerber.AllPoints();

        this.ctx.strokeStyle    = color;
        this.ctx.fillStyle      = color;

        this.ctx.beginPath();
        this.ctx.moveTo(this.ZoomedX(points[0][0]), this.ZoomedY(points[0][1]));
        for (var i = 0; i < points.length-1; i++) {
        this.ctx.lineTo(this.ZoomedX(points[i+0][0]), this.ZoomedY(points[i+0][1]));
        this.ctx.lineTo(this.ZoomedX(points[i+1][0]), this.ZoomedY(points[i+1][1]));
        if(fill) { this.ctx.fill(); } else { this.ctx.stroke(); }
        }
        this.ctx.closePath();
        
    } else {
        
        for (var i = 0; i < gerber.routes.length; i++) {
        var route = gerber.routes[i];
        var apperture = gerber.GetAppertureWithCode(route.cls);
        this.DrawRoute(gerber, route, apperture, colorObj );
        }
    }
    
};

VHGerberView.prototype.DrawExcellon = function(excellon,grbtype) {

    var color = this.colorScheme.GetLayerColor(grbtype);
 
    for(var i = 0; i < excellon.drills.length;i++ ) {
        var drill   = excellon.drills[i];
        var toolnr  = drill.type;
        var toolidx = excellon.hash_tools[toolnr];
        var tool    = excellon.tools[toolidx];
        this.DrawDrill(excellon, drill, tool, color);
    }
};

VHGerberView.prototype.DrawGerber = function(gerber,grbtype) {

    // this.ClearScreen();

    if(grbtype === "GKO") {
        this.DrawKeepout(gerber,grbtype);
    } else {
        var color = this.colorScheme.GetLayerColor(grbtype);
        var routes = gerber.routes.length;
        var polygons = gerber.polygons.length;

        for (var i = 0; i < polygons; i++) {
            var polygon = gerber.polygons[i];
            this.DrawPolygon(gerber, polygon, color);
        }

        for (var i = 0; i < routes; i++) {
            var route = gerber.routes[i];
            var apperture = gerber.GetAppertureWithCode(route.cls);
            this.DrawRoute(gerber, route, apperture, color );
            // if(i===822) { console.log( apperture,route ); }
        }
    }
    
    // this.vhcanvas.SavePicture("test");
};

VHGerberView.prototype.DrawAuto = function(grb,grbtype) {
    if(grb.type===1) { this.DrawGerber(grb,grbtype); }
    else { this.DrawExcellon(grb,grbtype); }
    this.vhcanvas.SavePicture("test");
};

VHGerberView.prototype.ShowXMMYMM = function(mouseX, mouseY) {
    
    var xy_mm = this.CalcXMMYMM(mouseX,mouseY);
    xmm = xy_mm.xmm.toFixed(2);
    ymm = xy_mm.ymm.toFixed(2);
    
    // console.log( "X:",xmm," Y:",ymm );
    /*    this.viewArea.screen_x, this.viewArea.screen_y,
    "zoomx:",this.viewArea.zoom_x, "zoomy:",this.viewArea.zoom_y); */
    
    var rx = 1;
    var ry = 677;
    
    function DrawText(x,y,t) { }
    
    var fone = "#141";
    var color = "#0E0";
    
    this.ctx.beginPath();
    this.ctx.strokeStyle = fone;
    this.ctx.fillStyle = fone;
    this.ctx.lineWidth = 1.0;
    this.ctx.rect(0.5+rx,0.5+ry, 240, 22 );
    this.ctx.fill();
    this.ctx.stroke();

    this.ctx.fillStyle = color;
    this.ctx.font = "16px Arial";
    this.ctx.fillText(xmm+" mm : "+ymm+" mm",rx+4,ry+16);
    // this.ctx.stroke();
    this.ctx.closePath();

    // $("#cssgview_info").html("");
    // $("#cssgview_info").append(mouseX + ":" + mouseY);
};

// Gerber   Visualization Methods
// Gerbers  Array Visualization

// Route:

/*
VHGerberVis.prototype.Init = function(divlays,divapps,divroutes,divinfo) {
  this.ShowAppertures(  $("#cssgview_appertures")   );
  this.ShowRoutes(      $("#cssgview_routes")       );
  this.MakeApperturesClickable();
};
*/

/*
VHGerberVis.prototype.Show = function() {

    // Request View parameters
    this.ctx.strokeStyle = "#900000";
    this.DrawGrid();
    
    for(var i=0;i<this.pcb.grbArray.length;i++) {
        // console.log(this.pcb.filestype[i]);
        if(this.pcb.filestype[i] === "DRL" ) {
            this.DrawExcellon(i);
        } else {
            this.DrawGerber(i);
        }
    }
    
    this.DrawOrigin();
};
*/

// ---------------------------
// Filling Sub-Pages content
// ---------------------------

/*
function LayerLine(name,type,color,pos) {
    this.name   = name;
    this.type   = type;
    this.color  = color;
    this.pos    = pos;
}

LayerLine.prototype.Show = function() { };
*/

