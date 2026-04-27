function VHCanvas() {
    
}

VHCanvas.prototype.InitFromObject = function(objCanvas) { 
    this.canvas = objCanvas;
    this.ctx = this.canvas.getContext("2d");
};

VHCanvas.prototype.InitFromID = function(canvasName) {
    this.canvas = document.getElementById(canvasName);
    this.ctx = this.canvas.getContext("2d");
};

VHCanvas.prototype.InitOffscreen = function(params) {
    this.canvas = JSDef.CreateCanvas(params);
    this.ctx = this.canvas.getContext("2d");
};

VHCanvas.prototype.DataURLPicture = function() {
    var image = this.canvas.toDataURL("image/png"); // "image/png" .replace("image/png", "image/octet-stream");
    return image;
};

VHCanvas.prototype.Width = function() { return this.canvas.width; };
VHCanvas.prototype.Height = function() { return this.canvas.height; };
VHCanvas.prototype.SetW = function(width) { this.ctx.lineWidth = width; };
VHCanvas.prototype.SetC = function(c) { this.ctx.strokeStyle = c; };
VHCanvas.prototype.SetF = function(c) { this.ctx.fillStyle = c; };

VHCanvas.prototype.Line = function(pf,pt) {
    this.ctx.beginPath();
    this.ctx.moveTo(pf.x,pf.y);
    this.ctx.lineTo(pt.x,pt.y);
    this.ctx.stroke();
    this.ctx.closePath();
};

VHCanvas.prototype.Poly = function(objVHPoint2DArr) {
    this.ctx.beginPath();
    this.ctx.moveTo(objVHPoint2DArr.arr[0].x,objVHPoint2DArr.arr[0].y);
    for(var i=1;i<objVHPoint2DArr.arr.length;i++) { this.ctx.lineTo(objVHPoint2DArr.arr[i].x,objVHPoint2DArr.arr[i].y); }
    this.ctx.stroke();
    this.ctx.fill();
    this.ctx.closePath();
    // console.log(objVHPoint2DArr);
};

VHCanvas.prototype.Arc = function(pc,r,pf,pt,dir) {
    
    /* console.log("Arc: center=",pc);
    console.log("radius=",r);
    console.log("from:",pf);
    console.log("to",pt);
    console.log(dir); */

    var a1 = pc.Angle(pf); // ((180-45) * Math.PI * 2)/360; // 2.35
    var a2 = pc.Angle(pt); // (0 * Math.PI * 2)/360; // + (Math.PI/2); // pc.Angle(pt);
   
    this.ctx.beginPath();
    this.ctx.arc(pc.x,pc.y, r, a1, a2, dir); // Math.PI*2
    this.ctx.stroke();
    this.ctx.closePath();
};

VHCanvas.prototype.SharpLine = function(pf,pt) {
    this.ctx.beginPath();
    this.ctx.moveTo(0.5 + Math.floor(pf.x), 0.5 + Math.floor(pf.y));
    this.ctx.lineTo(0.5 + Math.floor(pt.x), 0.5 + Math.floor(pt.y));
    this.ctx.stroke();
    this.ctx.closePath();
};

VHCanvas.prototype.Rect = function(pc,w,h) {
    this.ctx.beginPath();
    this.ctx.rect(pc.x, pc.y, w, h);
    this.ctx.fill();
    this.ctx.stroke();
    this.ctx.closePath();
};

VHCanvas.prototype.RectNF = function(pc,w,h) {
    this.ctx.beginPath();
    this.ctx.rect(pc.x, pc.y, w, h);
    // this.ctx.fill();
    this.ctx.stroke();
    this.ctx.closePath();
};


VHCanvas.prototype.RectO = function(pc,w,h) {
    this.ctx.beginPath();
    this.ctx.rect(pc.x, pc.y, w, h);
    this.ctx.fill();
    this.ctx.stroke();
    this.ctx.closePath();
};

VHCanvas.prototype.Circle = function(pc,r) {
    this.ctx.beginPath();
    this.ctx.arc(pc.x,pc.y,r,0,Math.PI*2,false); // Math.PI*2
    this.ctx.fill();
    this.ctx.stroke();
    this.ctx.closePath();
};

VHCanvas.prototype.Clear = function(color) {
	  this.SetF(color);
	  this.SetC(color);
	  this.Rect({x:0,y:0},this.Width(),this.Height());
};


// console.log("Warn !",route,apperture);
// JSDef.Abort("End");

/*
    VHCanvas.prototype.ArcTo = function(pc,r) {
    this.ctx.beginPath();
    this.ctx.arc(pc.x,pc.y,r,0,Math.PI*2,true);
    this.ctx.closePath();
    this.ctx.stroke();
};
*/

