/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito;


import gerenciadorCredito.Model.Lojista;
import br.com.caelum.vraptor.ioc.*;

/**
 *
 * @author vanderson
 */
@Component
@SessionScoped
public class LojistaSession {
    
    private Lojista user;

    public boolean isLogged() {
        return user != null;
    }

    public void logout() {
        user = null;
    }

    public Lojista getUser() {
        return user;
    }

    public void setUser(Lojista user) {
        this.user = user;
    }
    
    
}
