

use <myshapes.scad>

/*
	Saul Castro
	Updated 3/16/17
	
	This is a case for an 8x ws2812 rgb led module.
	
	its part of my programable led tail light for RC tx/rx system.
	
	The code is laidout in small module for good programming pratices, 
	reuseable module make repeated/symmetrical items easy.
	This also make section easy to reuse in other designs and saves time when
	adding or modifying features.
	
	note: this openscad is based on my own helper file "myshapes.scad"
	This is a set of short hand module that try to simplify the scad syntax, where is openpycad? 
	
	first of letter of basic shapes, and all parameters in order (x, y, z, a, b,..)
	r prefix and additional parameter make the shape with rounded edges. (compensated hull)
	ex: rectangle of 10 x 20 x 30 = c(10, 20, 30);
		rounded cube of 10^3 and 1mm radius on z edges = rc(10, 10, 10, 1);
		
*/

w = 60;		//x
l = 5;		//y
d = 12;		//z

c = 4;		//curve
wall = 2;		//...

fn= 50;	//smoothness//# of polygons

//translate([20,12, wall])   c(10, 10, 10);

difference(){
	shell();					//outsite
	translate([0,0, 0])   cut();	//insdie
	
		translate([0,5, 1]) rotate([90,0,0])   cy(4, 8, fn);	//wire cut
}

//for slide on cover, not used
module slide(){
	
	hull(){
	translate([-(w/2-1),l/2, d]) rotate([90,0,0])   cy(2, l*2, fn);
	translate([(w/2-1),l/2, d]) rotate([90,0,0])   cy(2, l*2, fn);
	}
}

module hs(){
	difference(){
		union(){
			//reinforcement, not needed
//				hull(){
//				translate([2,0, 0]) c(14, 12, 2);
//				translate([2,0, 3]) c(16, 2, 6);
//				}
				hull(){
			
				translate([2,0, 0]) c(15, 2, 2);
				translate([0,24, 0])   rotate([0,0, 0]) cy(12, 2, 6);

				}
		}
		hull(){
		translate([0,23, 0])   cy(5.1, 8, fn);
			translate([0,16, 0])   cy(5.1, 8, fn);
		}
	}

}

//outside
module shell(){
	union(){
			translate([42/2,l, 1])  hs();
			translate([-42/2,l, 1])  mirror() hs();
		
		hull(){
			translate([0,l/2, d/2+ wall/2])   rrc(w+wall*2, l+ wall*2, d+wall, c, c);
			translate([0,0,d-3])  sp(10);
		}
	}
}

//inside
module cut(){
	
	translate([0,l/2, d/2]) rc(w, l, d, c);

}







