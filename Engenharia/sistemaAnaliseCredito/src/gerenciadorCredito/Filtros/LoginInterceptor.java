/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Filtros;

import br.com.caelum.vraptor.*;
import gerenciadorCredito.Controle.LoginController;
import gerenciadorCredito.LojistaSession;
import gerenciadorCredito.Public;
import br.com.caelum.vraptor.core.InterceptorStack;
import br.com.caelum.vraptor.interceptor.Interceptor;
import br.com.caelum.vraptor.resource.ResourceMethod;

/**
 *
 * @author vanderson
 */
@Intercepts
public class LoginInterceptor implements Interceptor {

    private Result result;
    private LojistaSession userSession;

    public LoginInterceptor(Result result, LojistaSession userSession) {
        this.result = result;
        this.userSession = userSession;
    }

    public boolean accepts(ResourceMethod method) {
        return 
            !(method.getMethod().isAnnotationPresent(Public.class) ||
            method.getResource().getType().isAnnotationPresent(Public.class));
    }

    public void intercept(InterceptorStack stack, ResourceMethod method, Object resourceInstance) {
        if (userSession.isLogged()) {
            stack.next(method, resourceInstance);
        } else {
            result.redirectTo(LoginController.class).login();
        }
    }

}