/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lp.view.Logic;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author vanderson
 */
public class SalvaArquivo {
    private FileOutputStream fos;
    private DataOutputStream dos;

    public SalvaArquivo(String nome,String txt) {
        salva(nome,txt);
        close();
    }
    File file;
    private void salva(String nome,String txt) {
        try {
            file = new File(nome+".txt");
            System.out.println(file.getAbsolutePath());
            fos = new FileOutputStream(file);
            dos = new DataOutputStream(fos);
            dos.writeUTF(txt);
        } catch (IOException ex) {
            Logger.getLogger(SalvaArquivo.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void close() {
        try {
            dos.close();
            fos.close();
        } catch (IOException ex) {
            Logger.getLogger(SalvaArquivo.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
