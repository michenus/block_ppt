<?php 
/**
* Возврат формы
*/
function kraus_ppt_tableWeigth($files, $files_get = NULL){
	$form = array();
	
  return $form;
}

/**
* Конфигурация формы в блоке (перетаскивание)
*/
function kraus_ppt_block_admin_configure_form($variables) {
  $form = $variables['form'];

  // Initialize the variable which will store our table rows.
  $rows = array();
  // строка проверка содержимого изображений
  //dpm($form['ppt_images_items']);
  // Iterate over each element in our $form['example_items'] array.
  foreach (element_children($form['ppt_images_items']) as $id) {

    // Before we add our 'weight' column to the row, we need to give the
    // element a custom class so that it can be identified in the
    // drupal_add_tabledrag call.
    //
    // This could also have been done during the form declaration by adding
    // '#attributes' => array('class' => 'example-item-weight'),
    // directy to the 'weight' element in tabledrag_example_simple_form().
    $form['ppt_images_items'][$id]['weight']['#attributes']['class'] = array('example-item-weight');

    // We are now ready to add each element of our $form data to the $rows
    // array, so that they end up as individual table cells when rendered
    // in the final table.  We run each element through the drupal_render()
    // function to generate the final html markup for that element.
    $rows[] = array(
      'data' => array(
        $form['ppt_images_items'][$id]['img'],
        $form['ppt_images_items'][$id]['name'],
        // Add our 'weight' column.
        drupal_render($form['ppt_images_items'][$id]['weight']),
      ),
      // To support the tabledrag behaviour, we need to assign each row of the
      // table a class attribute of 'draggable'. This will add the 'draggable'
      // class to the <tr> element for that row when the final table is
      // rendered.
      'class' => array('draggable'),
    );
  }

  // We now define the table header values.  Ensure that the 'header' count
  // matches the final column count for your table.
  $header = array(t('Превью'), t('Имя картинки'), t('Weight'));

  // We also need to pass the drupal_add_tabledrag() function an id which will
  // be used to identify the <table> element containing our tabledrag form.
  // Because an element's 'id' should be unique on a page, make sure the value
  // you select is NOT the same as the form ID used in your form declaration.
  //$table_id = 'ppt-images-table';
  $table_id = 'example-items-table';

  // We can render our tabledrag table for output.
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));

  // And then render any remaining form elements (such as our submit button).
  $output .= drupal_render_children($form);

  // We now call the drupal_add_tabledrag() function in order to add the
  // tabledrag.js goodness onto our page.
  //
  // For a basic sortable table, we need to pass it:
  // - the $table_id of our <table> element,
  // - the $action to be performed on our form items ('order'),
  // - a string describing where $action should be applied ('siblings'),
  // - and the class of the element containing our 'weight' element.
  //drupal_add_tabledrag($table_id, 'order', 'sibling', 'ppt-images-item-weight');
  //drupal_add_tabledrag($table_id, 'match', 'parent', 'ppt-images-item-pid', 'ppt-images-item-pid', 'ppt-images-item-id', FALSE);
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'example-item-weight');
  // Because we also want to sort in addition to providing parenting, we call
  // the drupal_add_tabledrag function again, instructing it to update the
  // weight field as items at the same level are re-ordered.
  // drupal_add_tabledrag($table_id, 'order', 'sibling', 'ppt-images-item-weight', NULL, NULL, FALSE);
  return $output;
}