package gerenciadorCredito.Controle;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


import br.com.caelum.vraptor.Path;
import br.com.caelum.vraptor.Resource;
import br.com.caelum.vraptor.Result;
import gerenciadorCredito.Model.ConsultaInterna;
import gerenciadorCredito.Model.ConsultaInternaDados;
import java.util.ArrayList;


/**
 *
 * @author vanderson
 */
@Resource
public class MenuConsultaInternaController {
    	private final Result result;

	public MenuConsultaInternaController(Result result) {
		this.result = result;
	}

	@Path("/menuConsultaInterna")
	public void menuConsultaInterna() {
         
	}
        
        @Path("/consultarInternamente")
        public void consultarInternamente(ConsultaInternaDados consulta){
                result.include("resultado", new ConsultaInterna().consultarInternamente(consulta));
                result.redirectTo(ResultadosController.class).resultadoConsultaInterna();
        }
}
