$port=new-Object System.IO.Ports.SerialPort COM8,115200,None,8,one
$port.Open()
$port.WriteLine("...")
  $message=$port.ReadLine()
  Write-Output $message
$port.Close()

