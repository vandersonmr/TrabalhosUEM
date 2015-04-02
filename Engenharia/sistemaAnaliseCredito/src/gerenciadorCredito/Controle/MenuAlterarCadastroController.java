/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Controle;
import DAOs.LojistaDAO;
import br.com.caelum.vraptor.Path;
import br.com.caelum.vraptor.Resource;
import br.com.caelum.vraptor.Result;
import gerenciadorCredito.Model.Lojista;


/**
 *
 * @author vanderson
 */
@Resource
public class MenuAlterarCadastroController {
    	private final Result result;

	public MenuAlterarCadastroController(Result result) {
		this.result = result;
	}

        @Path("/cadastro")
	public void cadastro(Lojista lojista) {
            System.out.println(lojista.getEmail());
            LojistaDAO dao = new LojistaDAO();
            result.include("loj",dao.getLojista(lojista));
            result.forwardTo(MenuAlterarCadastroController.class).menuAlterarCadastro();
	}
        
        @Path("/menuAlterarCadastro")
	public void menuAlterarCadastro() {
            
	}
        
        
        @Path("/alterarCadastro")
	public void alterarCadastro(Lojista lojista) {
                LojistaDAO dao = new LojistaDAO();
                String msg;
                try{
                    dao.update(lojista);
                    msg = "Cadastro alterado com sucesso!";
                    result.include("msg", msg);
                }catch(Exception e){
                    msg = "Falha ao tentar alterar cadastro: CNPJ já cadastrado. <br>"+e;
                   result.include("msg", msg);
                }
                result.redirectTo(ResultadosController.class).resultadoMensagem(msg,4);
	}
}