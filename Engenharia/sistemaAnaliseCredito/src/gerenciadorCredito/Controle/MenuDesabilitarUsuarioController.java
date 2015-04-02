/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Controle;

import DAOs.LojistaDAO;
import br.com.caelum.vraptor.Path;
import br.com.caelum.vraptor.Resource;
import br.com.caelum.vraptor.Result;
import gerenciadorCredito.Model.CadastrarLojista;
import gerenciadorCredito.Model.Lojista;

/**
 *
 * @author vandersonmr
 */
@Resource
public class MenuDesabilitarUsuarioController {
      	private final Result result;

	public MenuDesabilitarUsuarioController(Result result) {
		this.result = result;
	}

        @Path("/menuDesabilitarUsuario")
        public void menuDesabilitarUsuario(){
            
        }
        
	@Path("/desabilitarUsuario")
	public void desabilitarUsuario(Lojista lojista) {
            LojistaDAO dao = new LojistaDAO();
            lojista.setAdmin(-1);
            dao.updateAdmin(lojista);
            result.include("msg", "Cadastro desabilitado!");
            result.redirectTo(ResultadosController.class).resultadoMensagem("Cadastro desabilitado!",2);
	}
}
