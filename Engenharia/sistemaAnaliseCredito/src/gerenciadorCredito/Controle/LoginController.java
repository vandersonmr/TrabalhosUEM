package gerenciadorCredito.Controle;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
import DAOs.LojistaDAO;
import br.com.caelum.vraptor.*;
import gerenciadorCredito.LojistaSession;
import gerenciadorCredito.Model.Lojista;
import gerenciadorCredito.Public;

/**
 *
 * @author vanderson
 */
@Resource
public class LoginController {

    private Result result;
    private LojistaSession userSession;
    private LojistaDAO lojistaDAO;

    public LoginController(Result result, LojistaSession userSession) {
        this.result = result;
        this.userSession = userSession;
        this.lojistaDAO = new LojistaDAO();

    }

    @Public
    @Get("/login")
    public void login() {
    }

    @Public
    @Post("/autenticar")
    public void autenticar(Lojista lojista) {
        System.out.println(lojista.getEmail() + "\n" + lojista.getPass());
        Lojista lojistaNoBD = lojistaDAO.getLojista(lojista);
        if (lojistaNoBD != null) {

            if (lojistaNoBD.getEmail().equals(lojista.getEmail())
                    && lojistaNoBD.getPass().equals(lojista.getPass())) {
                userSession.setUser(lojistaNoBD);
                
                
                if (lojistaNoBD.getAdmin() == 1) {
                    result.redirectTo(MenuAdminController.class).menuAdmin();
                }else if(lojistaNoBD.getAdmin() == -1) {
                    userSession.logout();
                    result.include("error", "Usuario desabilitado!")
                        .redirectTo(this).login();
                } else {
                    result.redirectTo(IndexController.class).index();
                }
            } else {
                result.include("error", "Senha incorreta!")
                        .redirectTo(this).login();
            }
        } else {
            result.include("error", "E-mail incorreto!")
                    .redirectTo(this).login();
        }
    }

    @Get("/logout")
    public void logout() {
        userSession.logout();
        result.redirectTo(this).login();
    }
}