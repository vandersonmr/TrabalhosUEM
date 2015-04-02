package gerenciadorCredito.Controle;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


import br.com.caelum.vraptor.Path;
import br.com.caelum.vraptor.Resource;
import br.com.caelum.vraptor.Result;

/**
 *
 * @author vanderson
 */
@Resource
public class MenuController {
    	private final Result result;

	public MenuController(Result result) {
		this.result = result;
	}

	@Path("/menu")
	public void menu() {
		
	}

}
