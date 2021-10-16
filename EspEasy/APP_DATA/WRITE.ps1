$port=new-Object System.IO.Ports.SerialPort COM6,115200,None,8,one
$port.Open()
$port.WriteLine("Save")
  $message=$port.ReadLine()
  Write-Output $message
$port.Close()

