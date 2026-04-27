function VHGerberFormat() { };

VHGerberFormat.prototype.InitFromArray = function(arr) {
    this.flagInch = arr[0]===1 ? true : false;
    this.xdim1 = arr[1]; this.xdim2 = arr[2]; this.ydim1 = arr[3]; this.ydim2 = arr[4];
};

VHGerberFormat.prototype.UnitsInInch = function() { return Math.pow(10,this.xdim2); };
VHGerberFormat.prototype.UnitsInCm = function() { var r = Math.pow(10,this.xdim2); return this.flagInch ? r / 2.54 : r; };

