/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package DAOs;

import gerenciadorCredito.Model.Lojista;

/**
 *
 * @author vanderson
 */
public class mainTeste {

    public static void main(String args[]) {
  
        HistoricoDAO dao = new HistoricoDAO();
        dao.getEstatisticas();
        dao.close();
    }
}
