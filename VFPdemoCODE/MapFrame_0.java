package be2d;

public class MapFrame_0 extends javax.swing.JFrame {
    private javax.swing.JPanel jPanel1;
    private javax.swing.JButton[] jB;
    private javax.swing.JMenu jMenu1;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JMenuItem jMenuItem1;

    public MapFrame_0() {
        initComponents();
        createButtons(getParamsFromFile("vfp_output.txt", 100, 100));// distribution path
    }

    private void initComponents() {
        jPanel1 = new javax.swing.JPanel();
        this.add(jPanel1);
        jPanel1.setLayout(null);
        jPanel1.setBackground(new java.awt.Color(153, 100, 255));
        this.setBounds(300, 100, 800, 600);
        
        jMenuBar1 = new javax.swing.JMenuBar();
        jMenu1 = new javax.swing.JMenu();
        jMenuItem1 = new javax.swing.JMenuItem();

        jMenu1.setText("Office Floor Plan");
        jMenuItem1.setText("Refresh");
        jMenuItem1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem1ActionPerformed(evt);
            }
        });

        jMenu1.add(jMenuItem1);
        jMenuBar1.add(jMenu1);
        setJMenuBar(jMenuBar1);
    }

    private void jMenuItem1ActionPerformed(java.awt.event.ActionEvent evt) {
        String command = "vfp_demo2.exe";
        Runtime r = Runtime.getRuntime();
        try {
            r.exec(command);
        } catch (java.io.IOException e) {
            System.err.println(e.getMessage());
        }
        jPanel1.removeAll();
        createButtons(getParamsFromFile("vfp_output.txt", 100, 100));
        jPanel1.repaint();
    }

    public int file_rec_cnt = 0;
 
    public String[][] getParamsFromFile(String file_name, int arr_size_a, int arr_size_b) {
        String[][] param_holder;
        try {
            java.io.BufferedReader in = new java.io.BufferedReader(new java.io.FileReader(file_name));

            param_holder = new String[arr_size_a][arr_size_b];
            java.util.Scanner scanner;
            int x = 0;
            String s = new String();

            while ((s = in.readLine()) != null) {
                scanner = new java.util.Scanner(s);
                scanner.useDelimiter(",");
                int y = 0;
                while (scanner.hasNext()) {
                    param_holder[x][y++] = scanner.next().trim();
                }
                x++;
            }

            for (int c = 0; c < 10; c++) {
                for (int d = 0; d < 10; d++) {
                    System.out.print(param_holder[c][d]);
                }
                System.out.println();
            }

            in.close();

            file_rec_cnt = x;

            return param_holder;

        } catch (java.io.IOException e) {
            return null;
        }

    }

    public int createButtons(String[][] in_arr) {
        int num_of_butts = file_rec_cnt;

        jB = new javax.swing.JButton[num_of_butts];

        for (int ab = 0; ab < num_of_butts; ab++) {
            jB[ab] = new javax.swing.JButton();
            jB[ab].setBackground(new java.awt.Color(153, 153, 255));

            jB[ab].setSize(Integer.valueOf(in_arr[ab][4]) * 50, Integer.valueOf(in_arr[ab][3]) * 50);
            jB[ab].setText(in_arr[ab][0]);
            jB[ab].setLocation(Integer.valueOf(in_arr[ab][2]) * 50, Integer.valueOf(in_arr[ab][1]) * 50);
            jPanel1.add(jB[ab], null);

        }
        return 0;
    }

}
