/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Controle;


import br.com.caelum.vraptor.Path;
import br.com.caelum.vraptor.Resource;
import br.com.caelum.vraptor.Result;
import gerenciadorCredito.Model.CadastrarLojista;
import gerenciadorCredito.Model.Lojista;


/**
 *
 * @author vanderson
 */
@Resource
public class MenuNovoCadastroController {
    	private final Result result;

	public MenuNovoCadastroController(Result result) {
		this.result = result;
	}

	@Path("/menuNovoCadastro")
	public void menuNovoCadastro() {
     
	}
        
        @Path("/cadastrar")
        public void cadastrar(Lojista lojista){
                String msg = new CadastrarLojista().cadastrar(lojista);
                result.include("msg", msg);
                result.redirectTo(ResultadosController.class).resultadoMensagem(msg,0);
        }

        

}