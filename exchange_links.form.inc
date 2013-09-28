<?php
/**
 * Implements hook_form_alter()
 * @see exchange_links_hook_info_alter()
 */
function exchange_links_form_alter($form, $form_state) {
}

/**
 *  Implements hook_form_FORM_ID_alter()
 */
function exchange_links_form_block_admin_configure_alter(&$form, $form_state) {
  if ($form['module']['#value'] == 'exchange_links') {
    $form['actions']['exchange_links_delete'] = array(
      '#type' => 'submit',
      '#name' => 'exchange_links_delete',
      '#value' => t('Delete block'),
      '#submit' => array('exchange_links_delete_submit'),
    );
  }
}

function exchange_links_delete_submit($form, $form_state) {
  dpm($form);
  dpm($form_state);
}
