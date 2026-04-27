// ---------------------------------------
// Gerber Object {appertures} {routes}
// ---------------------------------------
function VHGerber() { };

VHGerber.prototype.type_gerber = 1;
VHGerber.prototype.type_excellon = 2;

VHGerber.prototype.IsTypeGerber = function() { return this.type_gerber === this.type; };

VHGerber.prototype.IsTypeExcellon = function() { return this.type_excellon === this.type;};

VHGerber.prototype.InitFromArray = function(binarray) {

    // console.log(binarray);

    if(binarray.data[0]==="VHGRB1.11") {
        
        this.type = this.type_gerber;
        
        // Fill appertures, according to index
        this.format = new VHGerberFormat(); 
        this.format.InitFromArray(binarray.data[1]);
        this.InitFromArray_Appertures(binarray.data[2]);
        this.InitFromArray_Routes(binarray.data[3]);
        this.polygons = binarray.data[4];
        return true;
    }

    if(binarray.data[0]==="VHEXCELLON-1.1") {
        
        this.type = this.type_excellon;
        
        this.format = new VHGerberFormat(); 
        this.format.InitFromArray(binarray.data[1]);

        var tools  = binarray.data[2];
        var drills = binarray.data[3];
    
        this.tools = [];
        this.drills = [];
        
        // Create tools stack
        this.hash_tools = new Array(); 
        for (var i = 0; i < 300; i++) { this.hash_tools.push(-1); }
         
        for(var i=0;i<tools.length;i++) { 
            var tool = new VHExcellonTool();
            var idx = tools[i][0];
            tool.SetIDX(idx);
            tool.SetC(tools[i][3]);
            this.hash_tools[idx] = i;
            this.tools.push(tool);
        }
        
        // Transfer drills
        for(var i=0;i<drills.length;i++) {
            var drill = drills[i];
            var newdrill = new VHExcellonDrill();
            newdrill.Set(drill[0],drill[1],drill[2]);
            this.drills.push(newdrill);
        }
        
        return true;
    }
    
    JSDef.Abort("Wrong Gerber format");
    return false;
};

VHGerber.prototype.InitFromBase64 = function(content) {
    var decoder = new Base64Decoder();
    var bin = decoder.Decode(content);
    var arr = decoder.ReCreateArray(bin, 0);
    return this.InitFromArray(arr);
};

VHGerber.prototype.InitFromArray_Appertures = function(apps) {

    this.hash_apps = new Array();  for (var i = 0; i < 300; i++) { this.hash_apps.push(-1); }
    this._apps = new Array(); 
    
    for (var i = 0; i < apps.length; i++) { 
        
        var nr = apps[i][1];
        this.hash_apps[nr] = i;
        
        var objApperture = new VHGerberApperture();
        objApperture.InitFromArray(apps[i]);
        this._apps.push(objApperture);
    }
};

VHGerber.prototype.InitFromArray_Routes = function(arr) {
    
    this.routes = new Array();
    for (var i = 0; i < arr.length; i++) {
        var src = arr[i];
        var routeObject = new VHGerberRoute(src[0]); // class
        routeObject.InitFromArray(src[1]);
        this.routes.push(routeObject);
    } 
};

VHGerber.prototype.AreaDrills = function() {
    var x_min; var y_min; var x_max; var y_max;
    
    if(!this.drills.length) { return { x_min : 0, y_min: 0, x_max: 0, y_max: 0 }; }
    x_min = this.drills[0].x; y_min = this.drills[0].y; x_max = this.drills[0].x; y_max = this.drills[0].y;

    for(var i=1;i<this.drills.length;i++) {
        if (this.drills[i].x < x_min) { x_min = this.drills[i].x; } 
        if (this.drills[i].y < y_min) { y_min = this.drills[i].y; }
        if (this.drills[i].x > x_max) { x_max = this.drills[i].x; }
        if (this.drills[i].y > y_max) { y_max = this.drills[i].y; }
    }
    
    return { x_min : x_min, y_min: y_min, x_max: x_max, y_max: y_max,  w: x_max - x_min, h: y_max - y_min };
};

VHGerber.prototype.AreaGerber = function() {
    var x_min=0, y_min=0, x_max=0, y_max=0;
    // if(!this.routes.length) { return { x_min : 0, y_min: 0, x_max: 0, y_max: 0 }; }
    var areaFirst = this.routes[0].Area();
    x_min = areaFirst.x_min; y_min = areaFirst.y_min; x_max = areaFirst.x_max; y_max = areaFirst.y_max;

    for(var i=1;i<this.routes.length;i++) {
        var area = this.routes[i].Area();
        if (area.x_min < x_min) { x_min = area.x_min; } 
        if (area.y_min < y_min) { y_min = area.y_min; }
        if (area.x_max > x_max) { x_max = area.x_max; }
        if (area.y_max > y_max) { y_max = area.y_max; }
    }
    
    var poly_cnt = this.polygons.length;
    
    for(var j=0;j<poly_cnt;j++) {
        var poly = this.polygons[j];
        var pts = poly.length-1;
        for(var z=0;z<pts;z++) {
        if (poly[z][0] < x_min) { x_min = poly[z][0]; } 
        if (poly[z][1] < y_min) { y_min = poly[z][1]; }
        if (poly[z][0] > x_max) { x_max = poly[z][0]; }
        if (poly[z][1] > y_max) { y_max = poly[z][1]; }
        }
    }
    
    return { x_min : x_min, y_min: y_min, x_max: x_max, y_max: y_max,  w: x_max - x_min, h: y_max - y_min };
};

VHGerber.prototype.Area = function() {
    return this.IsTypeExcellon() ? this.AreaDrills() : this.AreaGerber();
};

VHGerber.prototype.AllPoints = function() {
    var result = [];
    for(var i=0;i<this.routes.length;i++) {
        var path = this.routes[i].path; 
        for(z=0;z<path.length;z++) { result.push(path[z]); }
    }
    return result;
};

VHGerber.prototype.GetApperturesCount = function() { return this._apps.length; };

VHGerber.prototype.GetAppertureWithCode = function(code) { 
    var idx = (code == 0) ? this.hash_apps[11] : this.hash_apps[code];
    var r = this._apps[idx];
    // console.log("Get Apperture With Code = ",idx,r);
    return r;
};

VHGerber.prototype.GetAppertureByIdx = function(idx) { return this._apps[idx]; };

// VHGerberObject.screen_x = 0; // VHGerberObject.screen_w/2;
// VHGerberObject.screen_y = 0; // VHGerberObject.screen_h/2;
// VHGerberObject.zoom_x = 1;
// VHGerberObject.zoom_y = 1;
// VHGerber_ShowGerber(VHGerberObject);

/* VHGerberObject = initObject;
 VHGerberObject.CenteringBoard();
 initObject.Show(); */

function GerberInit3DArray(types,routes) {
	
    var result_tracks = new Array();
    var result_pads = new Array();
	
	for(var j=0;j<routes.length;j++) {
		
		var dst = new Array();
		var elm = routes[j];
		var cnt = (elm.length-2)/2;
		var type = elm[0];
		var clid = elm[1];
		
		if(type==4) {
			var appno = VHGerber_SearchApperture(types,clid);
			if(appno!=-1)
			{
				var apptype = types[appno][1];
				var pnt3D 	= new VHGraph_CreatePoint(elm[2], elm[3]);
				
				if(apptype=='C') { 
					var apprad 	= types[appno][2];
					dst.push('C');
					dst.push(apprad);
					dst.push(pnt3D);
					result_pads.push(dst);
				} else 	if((apptype=='R')||(apptype=='O')) {
					var appw 	= types[appno][2] * 10;
					var apph 	= types[appno][3] * 10;
					dst.push(apptype);
					dst.push(appw);
					dst.push(apph);
					dst.push(pnt3D);
					result_pads.push(dst);
				} 

			}
		}
	}
		
	/* for(var i=0;i<cnt;i++) { var pnt3D = new Point3D(elm[2+(i*2)], elm[2+(i*2)+1], 0); dst.push(pnt3D); } */
	// result.push(dst);
	// for(var j=0;j<types)
	// console.log(routes);
	
	return result_pads;
}

//
VHGerber.prototype.ConvertToStack2D = function() {
	
	var stack2d = new VHStack2D();
	var stack2dp = new VHStack2D();

	var cnt = gerber.routes.length;
	
	for(var j=0;j<cnt;j++) {
		var groute = gerber.routes[j];
		var app = gerber.apps[groute.cls];
		var points = groute.path.length;
		
		if(points>1) {
			var p = new VHPath2D();
			for(var i=0;i<points;i++) { p.AddPointXY(groute.path[i][0],groute.path[i][1]); }
			stack2d.AddPath(0, 0, p, 1 );
		}
		else {
			if(app.type==1) 	{ stack2dp.AddCircle(groute.path[0][0], groute.path[0][1], app.v1, 1); }
			else if(app.type==2)	{ stack2dp.AddRect(groute.path[0][0], groute.path[0][1], app.v1, app.v2, 1); }
			else if(app.type==3)	{ stack2dp.AddOval(groute.path[0][0], groute.path[0][1], app.v1, app.v2, 1); }
			else console.log("catcha!");
		}
	}
	
	// Put appertures to the bottom of stack
	var result = new VHStack2D();
	result.objs = stack2d.objs.concat(stack2dp.objs); 
	
	return result;
};

//
VHGerber.prototype.ConvertToPaths3D = function() { 
	
	var resultt = new VHPaths3D();
	var resulta = new VHPaths3D();
	
	for(var j=0;j<this.routes.length;j++)
	{
		var groute  = this.routes[j];
		var points = groute.path.length;
		var app = this.apps[groute.cls];
		
		if(points>1) {
			var p = new VHPath3D(1);
			for(var i=0;i<points;i++) { p.AddPointXYZ(groute.path[i][0],groute.path[i][1],0); }
			resultt.Add(p);
		}
		else {

			var p = new VHPath3D(2);
			var x = groute.path[0][0];
			var y = groute.path[0][1];
			
			if(app.type==1) { // stack2dp.AddCircle(groute.path[0][0], groute.path[0][1], app.v1, 1);
				var pts = 12;
				var anglep = 2*Math.PI/pts;
				for(var i=0;i<(pts+1);i++) { p.AddPointXYZ(x + (app.v1*Math.cos(i*anglep)),y + (app.v1*Math.sin(i*anglep)),0); }
			}
			else if((app.type==2)||(app.type==3)) {
				var w2 = app.v1/2;
				var h2 = app.v2/2;
				p.AddPointXYZ(x-w2,y-h2,0);
				p.AddPointXYZ(x+w2,y-h2,0);
				p.AddPointXYZ(x+w2,y+h2,0);
				p.AddPointXYZ(x-w2,y+h2,0);
			}
			// else if(app.type==3)	{ stack2dp.AddOval(groute.path[0][0], groute.path[0][1], app.v1, app.v2, 1); }
			// else console.log("catcha!");

			resulta.Add(p);
			
		}
		
	}
	
	var result = new VHPaths3D();
	result.p = result.p.concat(resulta.p);
	
	return result;
};
