package lp;

import javax.swing.JFrame;
import lp.HotelAnimais.Acomodacao;
import lp.HotelAnimais.Especie;
import lp.HotelCachorros.Persistencia.BancoDeDados;
import lp.HotelAnimais.Porte;
import lp.HotelAnimais.PorteFaixa;
import lp.view.*;


/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author vanderson
 */
public class main extends javax.swing.JFrame {

    /**
     * Creates new form main
     */
    public main() {
        initComponents();
        criaFaixasDePorte();
        criarAcomodacoes();
    }

    private void criaFaixasDePorte() {
        PorteFaixa f1 = new PorteFaixa(0d, 20d, 0d, 30d, Especie.Cachorro,
                Porte.Pequeno);
        PorteFaixa f2 = new PorteFaixa(21d, 40d, 31d, 60d, Especie.Cachorro,
                Porte.Medio);
        PorteFaixa f3 = new PorteFaixa(41d, 60d, 61d, 80d, Especie.Cachorro,
                Porte.Grande);
        PorteFaixa gf1 = new PorteFaixa(0d, 20d, 0d, 30d, Especie.Gato,
                Porte.Pequeno);
        PorteFaixa gf2 = new PorteFaixa(21d, 40d, 31d, 60d, Especie.Gato,
                Porte.Medio);
        PorteFaixa gf3 = new PorteFaixa(41d, 60d, 61d, 80d, Especie.Gato,
                Porte.Grande);
        PorteFaixa pf1 = new PorteFaixa(0d, 5d, 0d, 5d, Especie.passaro,
                Porte.Pequeno);
        PorteFaixa pf2 = new PorteFaixa(5d, 10d, 5d, 10d, Especie.passaro,
                Porte.Medio);
        PorteFaixa pf3 = new PorteFaixa(10d, 30d, 10d, 30d, Especie.passaro,
                Porte.Grande);
        PorteFaixa pef1 = new PorteFaixa(0d, 2d, 0d, 2d, Especie.peixe,
                Porte.Pequeno);
        PorteFaixa pef2 = new PorteFaixa(2d, 5d, 2d, 5d, Especie.peixe,
                Porte.Medio);
        PorteFaixa pef3 = new PorteFaixa(5d, 10d, 5d, 10d, Especie.peixe,
                Porte.Grande);
        BancoDeDados.getInstance().getPortesFaixas().add(f1);
        BancoDeDados.getInstance().getPortesFaixas().add(f2);
        BancoDeDados.getInstance().getPortesFaixas().add(f3);
        BancoDeDados.getInstance().getPortesFaixas().add(gf1);
        BancoDeDados.getInstance().getPortesFaixas().add(gf2);
        BancoDeDados.getInstance().getPortesFaixas().add(gf3);
        BancoDeDados.getInstance().getPortesFaixas().add(pf1);
        BancoDeDados.getInstance().getPortesFaixas().add(pf2);
        BancoDeDados.getInstance().getPortesFaixas().add(pf3);
        BancoDeDados.getInstance().getPortesFaixas().add(pef1);
        BancoDeDados.getInstance().getPortesFaixas().add(pef2);
        BancoDeDados.getInstance().getPortesFaixas().add(pef3);
    }
    private int numAcomodacoesGrandes = 3 * 4;
    private int numAcomodacoesMedias = 2 * 4;
    private int numAcomodacoesPequenas = 5 * 4;

    private void criarAcomodacoes() {
        Acomodacao grandes[] = new Acomodacao[numAcomodacoesGrandes];
        Acomodacao medias[] = new Acomodacao[numAcomodacoesMedias];
        Acomodacao pequenas[] = new Acomodacao[numAcomodacoesPequenas];
        int i;
        for (i = 0; i < grandes.length / 4; i++) {
            grandes[i] = new Acomodacao(i, Porte.Grande, Especie.Cachorro);
            BancoDeDados.getInstance().getAcomodacoes().add(grandes[i]);
        }
        for (i = 0; i < medias.length / 4; i++) {
            medias[i] = new Acomodacao(i + numAcomodacoesGrandes, Porte.Medio, Especie.Cachorro);
            BancoDeDados.getInstance().getAcomodacoes().add(medias[i]);
        }
        for (i = 0; i < pequenas.length / 4; i++) {
            pequenas[i] = new Acomodacao(i + numAcomodacoesGrandes + numAcomodacoesMedias,
                    Porte.Pequeno, Especie.Cachorro);
            BancoDeDados.getInstance().getAcomodacoes().add(pequenas[i]);
        }

        ////**** Gatos *****///
        for (i = grandes.length / 4; i < grandes.length/2; i++) {
            grandes[i] = new Acomodacao(i, Porte.Grande, Especie.Gato);
            BancoDeDados.getInstance().getAcomodacoes().add(grandes[i]);
        }
        for (i = medias.length / 4; i < medias.length/2; i++) {
            medias[i] = new Acomodacao(i + numAcomodacoesGrandes, Porte.Medio, Especie.Gato);
            BancoDeDados.getInstance().getAcomodacoes().add(medias[i]);
        }
        for (i = pequenas.length / 4; i < pequenas.length/2; i++) {
            pequenas[i] = new Acomodacao(i + numAcomodacoesGrandes + numAcomodacoesMedias,
                    Porte.Pequeno, Especie.Gato);
            BancoDeDados.getInstance().getAcomodacoes().add(pequenas[i]);
        }
        
                ////**** Passaro *****///
        for (i = grandes.length / 2; i < 3*grandes.length/4; i++) {
            grandes[i] = new Acomodacao(i, Porte.Grande, Especie.passaro);
            BancoDeDados.getInstance().getAcomodacoes().add(grandes[i]);
        }
        for (i = medias.length / 2; i < 3*medias.length/4; i++) {
            medias[i] = new Acomodacao(i + numAcomodacoesGrandes, Porte.Medio, Especie.passaro);
            BancoDeDados.getInstance().getAcomodacoes().add(medias[i]);
        }
        for (i = pequenas.length / 2; i < 3*pequenas.length/4; i++) {
            pequenas[i] = new Acomodacao(i + numAcomodacoesGrandes + numAcomodacoesMedias,
                    Porte.Pequeno, Especie.passaro);
            BancoDeDados.getInstance().getAcomodacoes().add(pequenas[i]);
        }

                ////**** Peixes *****///
        for (i = 3*grandes.length/4 ; i < grandes.length; i++) {
            grandes[i] = new Acomodacao(i, Porte.Grande, Especie.peixe);
            BancoDeDados.getInstance().getAcomodacoes().add(grandes[i]);
        }
        for (i = 3*medias.length/4 ; i < medias.length; i++) {
            medias[i] = new Acomodacao(i + numAcomodacoesGrandes, Porte.Medio, Especie.peixe);
            BancoDeDados.getInstance().getAcomodacoes().add(medias[i]);
        }
        for (i = 3*pequenas.length/4 ; i < pequenas.length; i++) {
            pequenas[i] = new Acomodacao(i + numAcomodacoesGrandes + numAcomodacoesMedias,
                    Porte.Pequeno, Especie.peixe);
            BancoDeDados.getInstance().getAcomodacoes().add(pequenas[i]);
        }

    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        checkin = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();
        gerarEtiqueta = new javax.swing.JButton();
        jButton3 = new javax.swing.JButton();
        consultarAcomodacoes = new javax.swing.JButton();
        checkOut = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        checkin.setText("Check in");
        checkin.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                checkinActionPerformed(evt);
            }
        });

        jLabel1.setText("Gerenciador do Hotel de Animais");

        gerarEtiqueta.setText("Gerar etiqueta");
        gerarEtiqueta.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                gerarEtiquetaActionPerformed(evt);
            }
        });

        jButton3.setText("Gerar relatório");
        jButton3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton3ActionPerformed(evt);
            }
        });

        consultarAcomodacoes.setText("Consultar acomodações");
        consultarAcomodacoes.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                consultarAcomodacoesActionPerformed(evt);
            }
        });

        checkOut.setText("Check out");
        checkOut.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                checkOutActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(checkin, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(gerarEtiqueta, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 379, Short.MAX_VALUE)
                            .addComponent(jButton3, javax.swing.GroupLayout.DEFAULT_SIZE, 379, Short.MAX_VALUE)))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(93, 93, 93)
                        .addComponent(jLabel1)
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(consultarAcomodacoes, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(checkOut, javax.swing.GroupLayout.DEFAULT_SIZE, 379, Short.MAX_VALUE)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addGap(18, 18, 18)
                .addComponent(checkin)
                .addGap(18, 18, 18)
                .addComponent(gerarEtiqueta)
                .addGap(18, 18, 18)
                .addComponent(jButton3)
                .addGap(18, 18, 18)
                .addComponent(consultarAcomodacoes)
                .addGap(18, 18, 18)
                .addComponent(checkOut)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void consultarAcomodacoesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_consultarAcomodacoesActionPerformed
        ConsultaAcomodacaoView view = new ConsultaAcomodacaoView();
        view.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        view.show();
    }//GEN-LAST:event_consultarAcomodacoesActionPerformed

    private void checkOutActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_checkOutActionPerformed
        CheckOutView view = new CheckOutView();
        view.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        view.show();
    }//GEN-LAST:event_checkOutActionPerformed

    private void checkinActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_checkinActionPerformed
        CheckInView view = new CheckInView();
        view.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        view.show();
    }//GEN-LAST:event_checkinActionPerformed

    private void gerarEtiquetaActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_gerarEtiquetaActionPerformed
        EtiquetaView view = new EtiquetaView();
        view.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        view.show();
    }//GEN-LAST:event_gerarEtiquetaActionPerformed

    private void jButton3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton3ActionPerformed
        RelatorioView view = new RelatorioView();
        view.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        view.show();
    }//GEN-LAST:event_jButton3ActionPerformed

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
            java.util.logging.Logger.getLogger(main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                new main().setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton checkOut;
    private javax.swing.JButton checkin;
    private javax.swing.JButton consultarAcomodacoes;
    private javax.swing.JButton gerarEtiqueta;
    private javax.swing.JButton jButton3;
    private javax.swing.JLabel jLabel1;
    // End of variables declaration//GEN-END:variables
}
