import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;


public class Julia extends JFrame implements ActionListener{
	private final int maxIter = 300;
    private double cY, cX;
	JLabel lblReal;
	JLabel lblImaginary;
	JTextField txtReal;
	JTextField txtImaginary;
	JButton btnGen;
	JButton btnCancel;
	public Julia() {
		//setSize(new Dimension(400,200));
		setLayout(new GridLayout(3,2));
		lblReal = new JLabel("Real Part");
		lblImaginary = new JLabel("Imaginary Part");
		txtReal = new JTextField(20);
		txtImaginary = new JTextField(20);
		btnGen = new JButton("Generate");
		btnCancel = new JButton("Cancel");
		
		btnGen.addActionListener(this);
		btnCancel.addActionListener(this);
		
		add(lblReal);
		add(txtReal);
		add(lblImaginary);
		add(txtImaginary);
		add(btnGen);
		add(btnCancel);
		pack();
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
	}
	
	public static void main(String[] args) {
		new Julia();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == btnCancel) {
			//JOptionPane.showMessageDialog(this, "Cancel Clicked");
			dispose();
			setVisible(false);
		} else if (e.getSource() == btnGen) {
			double real = Double.parseDouble(txtReal.getText());
			double imaginary = Double.parseDouble(txtImaginary.getText());
			drawJulia(real,imaginary);
		}
		
	}

	private void drawJulia(double real, double imaginary) {
		int w = 3840;
        int h = 2160;
        BufferedImage image = new BufferedImage(w, h,
                BufferedImage.TYPE_INT_RGB);
        cX = real;
        cY = imaginary;
        double zx, zy;
 
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                zx = 1.5 * (x - w / 2) / (0.5 * w);
                zy = (y - h / 2) / (0.5 * h);
                float i = maxIter;
                while (zx * zx + zy * zy < 4 && i > 0) {
                    double tmp = zx * zx - zy * zy + cX;
                    zy = 2.0 * zx * zy + cY;
                    zx = tmp;
                    i--;
                }
                int c = Color.HSBtoRGB((maxIter / i) % 1, 1, i > 0 ? 1 : 0);
                image.setRGB(x, y, c);
            }
        }
        //g.drawImage(image, 0, 0, null);
        try{
            ImageIO.write(image,"png",new File("Julia.png"));    
        } catch(Exception e){
        	e.printStackTrace();
        }
	}

}
