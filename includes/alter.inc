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

use Drupal\uikit_admin\UIkitAdmin;

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

/**
 * Implements hook_theme_suggestions_HOOK_alter() for details templates.
 */
function uikit_admin_theme_suggestions_details_alter(array &$suggestions, array $variables) {
  $views_ui_tab_buckets = UIkitAdmin::getViewsUITabBuckets();
  $arguments = isset($variables['element']['arguments']) ? $variables['element']['arguments'] : [];
  $arguments_theme_wrappers = $arguments && isset($variables['element']['arguments']['#theme_wrappers']) ? $variables['element']['arguments']['#theme_wrappers'] : [];

  if ($arguments_theme_wrappers && array_intersect($views_ui_tab_buckets, $arguments_theme_wrappers)) {
    $suggestions = [
      'details',
      'details__views_ui_tabs',
    ];
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter() for input templates.
 */
function uikit_admin_theme_suggestions_input_alter(array &$suggestions, array $variables) {
  $views_ui_buttons = UIkitAdmin::getViewsUIButtons();
  $views_ui_dispay_buttons = UIkitAdmin::getViewsUIDisplayButtons();
  $type = $variables['element']['#type'];

  if ($type == 'submit') {
    if (is_object($variables['element']['#value'])) {
      $value = $variables['element']['#value']->getUntranslatedString();
    }
    else {
      $value = $variables['element']['#value'];
    }

    // Define a different template or Views UI display buttons.
    if (in_array($value, $views_ui_buttons) || in_array($value, $views_ui_dispay_buttons)) {
      $suggestions = [
        'input',
        'input__views_ui',
      ];
    }
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter() for links templates.
 */
function uikit_admin_theme_suggestions_links_alter(array &$suggestions, array $variables) {
  $views_ui_links = UIkitAdmin::getViewsUILinks();
  $id = isset($variables['attributes']['id']) ? $variables['attributes']['id'] : '';
  $classes = $variables['attributes']['class'];

  if (array_intersect($views_ui_links['class'], $classes) || in_array($id, $views_ui_links['id'])) {
    $suggestions = [
      'links',
      'links--views-ui'
    ];
  }
}
