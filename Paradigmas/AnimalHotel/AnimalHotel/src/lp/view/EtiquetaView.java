/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lp.view;

import java.util.Iterator;
import java.util.Set;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;
import lp.HotelAnimais.Acomodacao;
import lp.HotelAnimais.Animal;
import lp.HotelAnimais.Especie;
import lp.HotelAnimais.Estadia;
import lp.HotelCachorros.Persistencia.BancoDeDados;

/**
 *
 * @author vanderson
 */
public class EtiquetaView extends javax.swing.JFrame {

    /**
     * Creates new form Etiqueta
     */
    public EtiquetaView() {
       
        initComponents();
        preEncheValores();
    }
    Object aux[];

    private void preEncheValores() {
        valores.setListData(new Object[0]);
        String nomes[];

        if (filtro.getSelectedIndex() == 1) {

            aux = BancoDeDados.getInstance().getAnimais().toArray();
            Object[] ani = aux;
            nomes = new String[ani.length];
            for (int i = 0; i < ani.length; i++) {
                nomes[i] = ((Animal) ani[i]).getNome();
            }

        } else {

            aux = BancoDeDados.getInstance().getAcomodacoes().toArray();
            Object[] aco = aux;
            nomes = new String[aco.length];
            for (int i = 0; i < aco.length; i++) {
                Acomodacao c = ((Acomodacao) aco[i]);
                nomes[i] = c.getNum() + " - " + c.getEspecie() + " - " + c.getDimensao()
                        + " - " + c.getEstado();
            }

        }
        valores.setListData(nomes);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jRadioButton1 = new javax.swing.JRadioButton();
        jLabel1 = new javax.swing.JLabel();
        filtro = new javax.swing.JComboBox();
        jLabel2 = new javax.swing.JLabel();
        jScrollPane1 = new javax.swing.JScrollPane();
        valores = new javax.swing.JList();
        gerarCracha = new javax.swing.JButton();

        jRadioButton1.setText("jRadioButton1");

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        jLabel1.setText("Filtrar:");

        filtro.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Acomodações", "Animais" }));
        filtro.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                filtroActionPerformed(evt);
            }
        });

        jLabel2.setText("Escolha:");

        valores.setModel(new javax.swing.AbstractListModel() {
            String[] strings = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };
            public int getSize() { return strings.length; }
            public Object getElementAt(int i) { return strings[i]; }
        });
        valores.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        valores.setToolTipText("");
        jScrollPane1.setViewportView(valores);

        gerarCracha.setText("Gerar cracha");
        gerarCracha.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                gerarCrachaActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel1)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(filtro, 0, 316, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel2)
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addComponent(gerarCracha, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(filtro, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addComponent(jLabel2)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 196, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(gerarCracha)
                .addContainerGap(34, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void filtroActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_filtroActionPerformed
        preEncheValores();        // TODO add your handling code here:
    }//GEN-LAST:event_filtroActionPerformed

    private void gerarCrachaActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_gerarCrachaActionPerformed
        if (filtro.getSelectedIndex() == 1) {
            Animal ani = ((Animal) aux[valores.getSelectedIndex()]);
            Estadia est = BancoDeDados.getInstance().getEstadia(ani);
            if (est != null) {
                JOptionPane.showMessageDialog(null, new JTextArea("\n\n Animal: "
                        + ani.getNome() + "\n\nDono: " + ani.getDono().getNome() + "\n\nN. Acomodação: " +
                        est.getAcomodacao().getNum()), "Cracha", 1);
            }else{
                JOptionPane.showMessageDialog(null, "O Animal precisa estar hospedado!");
            }
        } else {
             Acomodacao aco = ((Acomodacao) aux[valores.getSelectedIndex()]);
             
             if(aco.getEstadia()!=null){
                  Animal ani = aco.getEstadia().getAnimal();
                  JOptionPane.showMessageDialog(null, new JTextArea("\n\n Animal: "
                        + ani.getNome() + "\n\nDono: " + ani.getDono().getNome() + "\n\nN. Acomodação: " +
                        aco.getNum()), "Cracha", 1);
             }else{
                   JOptionPane.showMessageDialog(null, "Acomodação sem animal hospedado!");
             }
        }

    }//GEN-LAST:event_gerarCrachaActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(EtiquetaView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(EtiquetaView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(EtiquetaView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(EtiquetaView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new EtiquetaView().setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JComboBox filtro;
    private javax.swing.JButton gerarCracha;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JRadioButton jRadioButton1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JList valores;
    // End of variables declaration//GEN-END:variables
}
