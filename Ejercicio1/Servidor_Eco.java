import java.net.*; // paquete que contienen clases de red , todo lo necesario para comunicarme en red
import java.io.*; // paquete que contienen clases para E/S teclado y monitor
import java.util.Scanner;


public class Servidor_Eco {

	DataOutputStream salida;
    
    public static void main(String[] args) throws IOException {
        
        if (args.length != 1) {
            System.err.println("Uso desde consola:  <numero puerto>");

            System.exit(1);
        }
        
        int numeroPuerto = Integer.parseInt(args[0]);// convertimos el numero de puerto
        
        try (
            ServerSocket socketdelServidor =
                new ServerSocket(Integer.parseInt(args[0]));//escuchando peticiones
            Socket socketdelCliente = socketdelServidor.accept();// se acepta la peticion     
           PrintWriter escritor =
                new PrintWriter(socketdelCliente.getOutputStream(), true);                   
            BufferedReader lector = new BufferedReader(
               new InputStreamReader(socketdelCliente.getInputStream()));
        ) {
            String linealeida;
            System.out.print("Espero n caracteres n=  " + lector.readLine()+"\n");
	    System.out.print("El servidor dice:  " + lector.readLine()+"\n");
            System.out.print("Escriba respuesta al cliente:");
            linealeida=System.console().readLine();
            //while ((linealeida = lector.readLine()) != null) {
             escritor.println(String.valueOf(linealeida.length()+1));
            escritor.println(linealeida);
        	//System.out.println("El cliente dice:" +lector.readLine()+ "\n");
        	//escritor.println("Lo que sea");
            //System.out.println("Se envio mensaje al cliente");

            //}
        } catch (IOException e) {
            System.out.println(" ocurrio una excepcion cuando intentamos escuchar "
                + numeroPuerto + " o esperando por una conexicon");
            System.out.println(e.getMessage());
        }
    }
}
