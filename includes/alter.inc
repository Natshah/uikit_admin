<?php

/**
 * @file
 * Modify structured content arrays.
 *
 * These hooks are called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * content structure has been built.
 *
 * If the theme wishes to act on the rendered HTML of the content rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_HOOK().
 *
 * @see drupal_render()
 * @see theme()
 */

/**
 * Implements hook_form_FORM_ID_alter() for comment_admin_overview.
 */
function uikit_admin_form_comment_admin_overview_alter(&$form, \Drupal\Core\Form\FormStateInterface $form_state, $form_id) {
  // Drupal core does not place the submit button in an actions container so we
  // first copy the submit element array to a variable, remove the original
  // submit element array from the form, then create an actions container and
  // place the copied submit variable inside the actions container. This is to
  // provide proper styling.
  $submit = $form['options']['submit'];
  unset($form['options']['submit']);
  $form['options']['actions'] = [
    '#type' => 'actions',
  ];
  $form['options']['actions']['submit'] = $submit;
}
