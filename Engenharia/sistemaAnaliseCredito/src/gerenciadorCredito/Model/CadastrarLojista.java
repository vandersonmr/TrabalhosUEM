/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Model;

import DAOs.LojistaDAO;

/**
 *
 * @author vandersonmr
 */
public class CadastrarLojista {
    public String cadastrar(Lojista lojista){
        LojistaDAO dao = new LojistaDAO();
        try{

            dao.insert(lojista);
            dao.close();
            return "Lojista Cadastrado com sucesso! Email; "+lojista.getEmail();
        }catch(Exception e){
            dao.close();
            return "Impossível cadastrar lojista: Dados já cadastrados!<br><br>";
        }
        
        
    }
}
