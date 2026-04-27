
function VHGUIProgressBar() {
    this.progressVal     = 0;
    this.progressSign    = 1;
}

VHGUIProgressBar.prototype.SetCanvas = function(canvasName) { 
    this.canvas = document.getElementById(canvasName);
    this.ctx = this.canvas.getContext("2d");
};

VHGUIProgressBar.prototype.SetLabel = function(text) { this.text = text; };
VHGUIProgressBar.prototype.SetPercents = function(prc) { this.prc = prc;};

VHGUIProgressBar.prototype.RuntimeColors = function() {
    var color = 200 + (this.progressVal * 5); var color1 = 4;
    var val = color.toString(16); var val1 = color1.toString(16);
    var c = "#" + val1 + val1 + val + val1 + val1;
    return c;
};

VHGUIProgressBar.prototype.Update = function() {

        if(this.progressSign===1) { this.progressVal++; } else { this.progressVal--; }
        if((this.progressVal===0)||(this.progressVal===10)) { this.progressSign *= -1; }
        
        var ctx = this.ctx;

        ctx.fillStyle = "#FFF";
        ctx.fillRect(0,0,this.canvas.width,this.canvas.height);
        
        ctx.fillStyle = this.RuntimeColors();
        ctx.fillRect(0,0,this.canvas.width * this.prc,this.canvas.height);

        ctx.font = "26px Arial";
        ctx.fillStyle   = "#0A0";
        ctx.strokeStyle = "#070";
        ctx.lineWidth = 1;

        var prc = (this.prc*100).toFixed(0) +"%";
        var dim = ctx.measureText(prc);
        var x = (this.canvas.width - dim.width) / 2;
        ctx.fillText(prc,   x,40);
        ctx.strokeText(prc, x,40);
        ctx.fillText(this.text,   10,40);
        ctx.strokeText(this.text, 10,40);
};
