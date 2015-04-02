

import br.com.caelum.vraptor.Path;
import br.com.caelum.vraptor.Resource;
import br.com.caelum.vraptor.Result;


/**
 *
 * @author vanderson
 */
@Resource
public class MenuBuscarCadastroController {
    	private final Result result;

	public MenuBuscarCadastroController(Result result) {
		this.result = result;
	}

	@Path("/menuBuscarCadastro")
	public void menuBuscarCadastro() {
         
	}
}