/* ------------------------------------------------------------------------ */
function VHGerberColorsScheme(name, gerberColors, sysColors, visibility) { 
    this.name           = name;
    this.gerberColors   = gerberColors;
    this.sysColors      = sysColors;
    this.visibility     = visibility;
}

VHGerberColorsScheme.prototype.GetLayerColor = function(layerType) {
    for(var i=0;i<this.gerberColors.length;i++) { if(layerType === this.gerberColors[i][0]) { return this.gerberColors[i][1]; } }
    return "white";
};

VHGerberColorsScheme.prototype.LayerVisibility = function(layerType) {
    if(this.visibility.length > 0 ) {
        for(var i=0;i<this.visibility.length;i++) { if(layerType === this.visibility[i]) { return true; } } return false; } 
    return true;
};

/* ------------------------------------------------------------------------ */
function VHGerberColorsSchemes() { this.Init(); }

VHGerberColorsSchemes.prototype.Init = function() {

   var visibility_all    = [ ];
   var visibility_top    = [ "GKO","GTL","GTP","GPT", "DRL", "GTO" ];
   
   var colors_def = [
        ["GBO", "#379"      ],
        ["GBP", "#003"      ],
        ["GBS", "#005"      ],
        ["GBL", "blue"      ],
        ["G2",  "#4169E1"   ],
        ["G1",  "orange"    ],
        ["GPT", "#CD5C5C"   ],
        ["GTS", "#DA70D6"   ],
        ["GTL", "red"       ],
        ["DRL", "#030"      ],
        ["GTO", "yellow"    ],
        ["GKO", "#F0F"      ] ];

   var colors_white = [
        ["GBO", "#379"      ],
        ["GBP", "#003"      ],
        ["GBS", "#005"      ],
        ["GBL", "blue"      ],
        ["G2",  "#4169E1"   ],
        ["G1",  "orange"    ],
        ["GPT", "#CC6"      ],
        ["GTS", "#CC6"      ],
        ["GTL", "#DDD"      ],
        ["DRL", "#222"      ],
        ["GTO", "#999"      ],
        ["GKO", new ComplexColor("#EEE",0,true) ] ];

   var colors_yellow = [
        ["GBO", "#379"      ],
        ["GBP", "#003"      ],
        ["GBS", "#005"      ],
        ["GBL", "blue"      ],
        ["G2",  "#4169E1"   ],
        ["G1",  "orange"    ],
        ["GPT", "#CD5C5C"   ],
        ["GTS", "#DA70D6"   ],
        ["GTL", "red"       ],
        ["DRL", "#030"      ],
        ["GTO", "yellow"    ],
        ["GKO", new ComplexColor("#FF0",0,true)  ] ];

   var colors_red = [
        ["GBO", "#379"      ],
        ["GBP", "#003"      ],
        ["GBS", "#005"      ],
        ["GBL", "blue"      ],
        ["G2",  "#4169E1"   ],
        ["G1",  "orange"    ],
        ["GTP", "#FF6"      ],
        ["GPT", "#FF6"      ],
        ["GTS", "#CD5C5C"   ],
        ["GTL", "#A00"      ],
        ["DRL", "#000"      ],
        ["GTO", "#FFF"      ],
        ["GKO", new ComplexColor("#600",0,true) ] ]; 

   var colors_green = [
        ["GBO", "#379"      ],
        ["GBP", "#003"      ],
        ["GBS", "#005"      ],
        ["GBL", "blue"      ],
        ["G2",  "#4169E1"   ],
        ["G1",  "orange"    ],
        ["GTP", "#FF6"      ],
        ["GPT", "#FF6"      ],
        ["GTS", "#CD5C5C"   ],
        ["GTL", "#080"      ],
        ["DRL", "#111"      ],
        ["GTO", "#FFF"      ],
        ["GKO", new ComplexColor("#050",0,true) ] ]; 

   var colors_blue = [
        ["GBO", "#379"      ],
        ["GBP", "#003"      ],
        ["GBS", "#005"      ],
        ["GBL", "blue"      ],
        ["G2",  "#4169E1"   ],
        ["G1",  "orange"    ],
        ["GTP", "#FF6"      ],
        ["GPT", "#FF6"      ],
        ["GTS", "#CD5C5C"   ],
        ["GTL", "#00D"      ],
        ["DRL", "#000"      ],
        ["GTO", "#FFF"      ],
        ["GKO", new ComplexColor("#007",0,true) ] ]; 

   var colors_black = [
        ["GBO", "#379"      ],
        ["GBP", "#003"      ],
        ["GBS", "#005"      ],
        ["GBL", "blue"      ],
        ["G2",  "#4169E1"   ],
        ["G1",  "orange"    ],
        ["GTP", "#FF6"      ],
        ["GPT", "#FF6"      ],
        ["GTS", "#CD5C5C"   ],
        ["GTL", "#2A2A2A"   ],
        ["DRL", "#DDD"      ],
        ["GTO", "#FFF"      ],
        ["GKO", new ComplexColor("#111",0,true) ] ]; 


   var colors_sys_def   = { background : "black",  grid: "#444", grid2: "#333" };
   var colors_sys_grn   = { background : "black",  grid: "#333", grid2: "#333" };
   var colors_sys_black = { background : "#DDD",   grid: "#BBB", grid2: "#333" };
   // var colors_sys_def = { background : "black",  grid: "#СС44", grid2: "#333" };
   // var sysPal1 = { background : "black",  grid: "#444", grid2: "#333" };
    
   this.schemes = [];
   this.schemes.push( new VHGerberColorsScheme("Default",   colors_def,     colors_sys_def,     visibility_all ));
   this.schemes.push( new VHGerberColorsScheme("White",     colors_white,   colors_sys_def,     visibility_top ));
   this.schemes.push( new VHGerberColorsScheme("Yellow",    colors_yellow,  colors_sys_def,     visibility_top ));
   this.schemes.push( new VHGerberColorsScheme("Red",       colors_red,     colors_sys_def,     visibility_top ));
   this.schemes.push( new VHGerberColorsScheme("Green",     colors_green,   colors_sys_grn,     visibility_top ));
   this.schemes.push( new VHGerberColorsScheme("Blue",      colors_blue,    colors_sys_def,     visibility_top ));
   this.schemes.push( new VHGerberColorsScheme("Black",     colors_black,   colors_sys_black,   visibility_top ));
    
};

VHGerberColorsSchemes.prototype.Count   = function() { return this.schemes.length; };
VHGerberColorsSchemes.prototype.Get     = function(idx) { return this.schemes[idx]; };

// this.schemesNames = [ "Def", "Red", "Green", "Green", "Blue", "White" ];
// this.colors = ['red','DarkOrange','Fuchsia', 'blue'];
// scheme: gerberColors, systemColors, layersEnabled, "Default"

