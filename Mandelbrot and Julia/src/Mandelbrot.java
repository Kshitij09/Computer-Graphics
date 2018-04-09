import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;

public class Mandelbrot {
	public static void main(String args[]) throws Exception{
		int width = 3840, height = 2160;			//Width and height of image
		double x=0.0,y=0.0,x_new;
		double c_re,c_im;
		int iterations = 0;
		BufferedImage image = new BufferedImage(width,height,BufferedImage.TYPE_INT_RGB);
		//Maximum number of iterations for blown up condition
		int max = 1500;
		Color color = new Color(255,0,0);
		int black = 0x000000;
		/* In a complex plane, Y-axis represents imaginary part
		 * and X-axis represents real part
		 */
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				c_re = (col-width/2) * 4.0 / width;
				c_im = (row-height/2) * 4.0 / width;
				iterations = 0;
				x = 0; 
				y = 0;
				while (Math.sqrt(x*x+y*y) <= 2 && iterations < max) {
					x_new = (x*x-y*y) + c_re;
					y = (2*x*y) + c_im;
					x = x_new;
					iterations++;
				}
				if (iterations < max) {
					//function stays small, not blown up
					color = new Color(iterations*iterations%256,0,0);
					image.setRGB(col,row,color.getRGB());
				} else{
					//Blown up
					image.setRGB(col,row,black);
				}					
			}
		}
		ImageIO.write(image,"png",new File("Mandelbrot.png"));
	}
}