<?php
include_once "connection.php";

$conn = connection();

$display = "";

$sql = "SELECT * FROM sensor_data";
$data = $conn->query($sql);

while ($row = $data->fetch_assoc()) {
    $display .= "<tr>
                    <th>".$row['temperature']."</th>
                    <th>".$row['light']."</th>
                    <th>".$row['smoke']."</th>
                    <th>".$row['date_created']."</th>
                </tr>";
}

?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LGT System</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="stylesheet" href="//cdn.datatables.net/1.13.3/css/jquery.dataTables.min.css">
    <script src="js/script.js"></script>
</head>
<body>
<h1 style="text-align: center">Light, Smoke/Gas, & Temperature Monitoring System</h1>
    <div class="container p-3 bg-light" style="border:3px solid black;">
        <table class="table table-bordered table-striped dataTable dtr-inline p-3" id="sensor_table">
            <thead>
                <tr>
                    <th>Temperature</th>
                    <th>Light</th>
                    <th>Smoke</th>
                    <th>Date</th>
                </tr>
            </thead>
            <tbody>
                <?php echo $display; ?>
            </tbody>
        </table>
    </div>
</body>
<script src="https://code.jquery.com/jquery-3.6.3.js"></script>
<script src="//cdn.datatables.net/1.13.3/js/jquery.dataTables.min.js"></script>
<script>
    $(function () {
        $('#sensor_table').DataTable();

        setInterval(() => {
           location.reload();
        }, 2500);
    });
    
</script>
</html>