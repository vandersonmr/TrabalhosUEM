/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Filtros;

import br.com.caelum.vraptor.*;
import gerenciadorCredito.Controle.LoginController;
import gerenciadorCredito.LojistaSession;
import gerenciadorCredito.Admin;
import br.com.caelum.vraptor.core.InterceptorStack;
import br.com.caelum.vraptor.interceptor.Interceptor;
import br.com.caelum.vraptor.resource.ResourceMethod;

/**
 *
 * @author vanderson
 */
@Intercepts
public class AdminInterceptor implements Interceptor {

    private Result result;
    private LojistaSession userSession;

    public AdminInterceptor(Result result, LojistaSession userSession) {
        this.result = result;
        this.userSession = userSession;
    }

    public boolean accepts(ResourceMethod method) {
        return 
            (method.getMethod().isAnnotationPresent(Admin.class) ||
            method.getResource().getType().isAnnotationPresent(Admin.class));
    }

    public void intercept(InterceptorStack stack, ResourceMethod method, Object resourceInstance) {
        if (userSession.isLogged() && (userSession.getUser().getAdmin() == 1)) {
            stack.next(method, resourceInstance);
        } else {
            result.include("error", "Sem permissão!!").redirectTo(LoginController.class).login();
        }
    }

}