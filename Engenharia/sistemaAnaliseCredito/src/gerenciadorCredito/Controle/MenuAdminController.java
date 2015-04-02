/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Controle;
import br.com.caelum.vraptor.Path;
import br.com.caelum.vraptor.Resource;
import br.com.caelum.vraptor.Result;
import gerenciadorCredito.Admin;

/**
 *
 * @author vanderson
 */
@Resource
public class MenuAdminController {
    	private final Result result;

	public MenuAdminController(Result result) {
		this.result = result;
	}

        @Admin
	@Path("/menuAdmin")
	public void menuAdmin() {
		
	}

}
