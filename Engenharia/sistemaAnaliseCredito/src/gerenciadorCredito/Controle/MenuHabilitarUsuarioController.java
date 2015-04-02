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
public class MenuHabilitarUsuarioController {
      	private final Result result;

	public MenuHabilitarUsuarioController(Result result) {
		this.result = result;
	}

        @Path("/menuHabilitarUsuario")
        public void menuHabilitarUsuario(){
            
        }
        
	@Path("/habilitarUsuario")
	public void habilitarUsuario(Lojista lojista) {
            LojistaDAO dao = new LojistaDAO();
            lojista.setAdmin(0);
            dao.updateAdmin(lojista);
            result.include("msg", "Cadastro habilitado!");
            result.redirectTo(ResultadosController.class).resultadoMensagem("Cadastro habilitado!",1);
	}
}
