<?php

/**
 * @file
 * The theme system, which controls the output of the UIkit Admin theme.
 */

/**
 * Implements theme_admin_page().
 */
function uikit_admin_admin_page($variables) {
  $blocks = $variables['blocks'];

  $stripe = 0;
  $container = array();

  foreach ($blocks as $block) {
    if ($block_output = theme('admin_block', array('block' => $block))) {
      if (empty($block['position'])) {
        // Perform automatic striping.
        $block['position'] = ++$stripe % 2 ? 'left' : 'right';
      }
      if (!isset($container[$block['position']])) {
        $container[$block['position']] = '';
      }
      $container[$block['position']] .= $block_output;
    }
  }

  $output = '<div class="admin uk-grid">';
  $output .= theme('system_compact_link');

  foreach ($container as $id => $data) {
    $output .= '<div class="uk-width-small-1-1 uk-width-medium-1-2">';
    $output .= $data;
    $output .= '</div>';
  }

  $output .= '</div>';
  return $output;
}

/**
 * Implements theme_admin_block().
 */
function uikit_admin_admin_block($variables) {
  $block = $variables['block'];
  $output = '';

  // Don't display the block if it has no content to display.
  if (empty($block['show'])) {
    return $output;
  }

  $output .= '<div class="uk-panel uk-panel-box uk-panel-header uk-margin-bottom">';

  if (!empty($block['title'])) {
    $output .= '<h3 class="uk-panel-title uk-text-bold uk-text-uppercase">' . $block['title'] . '</h3>';
  }

  if (!empty($block['content'])) {
    $output .= '<div class="body">' . $block['content'] . '</div>';
  }
  else {
    $output .= '<div class="description">' . $block['description'] . '</div>';
  }

  $output .= '</div>';

  return $output;
}

/**
 * Implements theme_admin_block_content().
 */
function uikit_admin_admin_block_content($variables) {
  $content = $variables['content'];
  $output = '';

  if (!empty($content)) {
    $classes = 'uk-list uk-list-line uk-margin-remove uk-admin-list';

    if (system_admin_compact_mode()) {
      $classes .= ' uk-admin-list-compact';
    }

    $output .= '<ul class="' . $classes . '">';

    foreach ($content as $item) {
      $item['localized_options']['attributes']['class'][] = 'uk-text-bold';
      $output .= '<li>';

      if (!system_admin_compact_mode()) {
        $output .= '<i class="uk-icon-chevron-circle-right uk-text-muted uk-display-inline-block uk-admin-vertical-align-top" style="margin-top: 2px"></i>';
        $output .= '<div class="uk-margin-left uk-display-inline-block">';
        $output .= l($item['title'], $item['href'], $item['localized_options']);
      }
      else {
        $output .= l($item['title'], $item['href'], $item['localized_options']);
      }

      if (isset($item['description']) && !system_admin_compact_mode()) {
        $output .= '<div class="uk-text-muted">' . filter_xss_admin($item['description']) . '</div>';
      }

      if (!system_admin_compact_mode()) {
        $output .= '</div>';
      }

      $output .= '</li>';
    }

    $output .= '</ul>';
  }
  return $output;
}

/**
 * Implements theme_breadcrumb().
 */
function uikit_admin_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  $output = '';

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .uk-hidden.
    $output .= '<h2 class="uk-hidden">' . t('You are here') . '</h2>';

    $output .= '<ul class="uk-breadcrumb">';

    foreach ($breadcrumb as $crumb) {
      $output .= '<li>' . $crumb . '</li>';
    }

    $output .= '</ul>';
  }

  return $output;
}

/**
 * Implements theme_button() for views add display buttons.
 */
function uikit_admin_button__views_add_display($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));
  $element['#attributes']['class'] = array('add-display');

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Implements theme_button() for views edit buttons.
 */
function uikit_admin_button__views_edit_view($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Implements theme_container() for views edit buttons.
 */
function uikit_admin_container__views_view_edit($variables) {
  $element = $variables['element'];
  // Ensure #attributes is set.
  $element += array('#attributes' => array());
  $element['#attributes']['class'] = array('form-actions', 'js-hide', 'uk-float-right', 'uk-margin-remove');

  // Special handling for form elements.
  if (isset($element['#array_parents'])) {
    // Assign an html ID.
    if (!isset($element['#attributes']['id'])) {
      $element['#attributes']['id'] = $element['#id'];
    }
    // Add the 'form-wrapper' class.
    $element['#attributes']['class'][] = 'form-wrapper';
  }

  return '<div' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</div>';
}

/**
 * Implements theme_fieldset().
 */
function uikit_admin_fieldset__collapsible($variables) {
  $element = $variables['element'];
  $collapsed = $element['#collapsed'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array(
    'uk-panel',
    'uk-panel-box',
    'uk-admin-panel-box-toggle',
    'form-wrapper',
  ));
  $id = $element['#attributes']['id'];

  // When viewing the theme settings page for a specific theme, add the
  // .uk-admin-panel-box-light class to theme nested fieldsets.
  if (substr(current_path(), 0, 26) === 'admin/appearance/settings/') {
    $theme_key = arg(3);
    $all_regions = system_region_list($theme_key);

    $theme_settings = array(
      'edit-meta-viewport' => 'edit-meta-viewport',
      'edit-standard-layout' => 'edit-standard-layout',
      'edit-tablet-layout' => 'edit-tablet-layout',
      'edit-mobile-layout' => 'edit-mobile-layout',
      'edit-navbar-container-settings' => 'edit-navbar-container-settings',
      'edit-navbar-margin' => 'edit-navbar-margin',
    );

    foreach ($all_regions as $region_key => $region) {
      $region_id = 'edit-' . str_replace('_', '-', $region_key);

      if (!in_array($region_id, $theme_settings)) {
        $theme_settings[$region_id] = $region_id;
      }
    }

    if (in_array($id, $theme_settings)) {
      $element['#attributes']['class'][] = 'uk-admin-panel-box-light';
    }
  }

  $output = '<div' . drupal_attributes($element['#attributes']) . '>';

  if (!empty($element['#title'])) {
    $output .= '<h3 class="uk-panel-title uk-admin-panel-title-toggle">';
    $toggle_attributes = array(
      'data-uk-toggle' => "{target:'#" . $id . "-toggle'}",
    );

    $output .= '<a' . drupal_attributes($toggle_attributes) . '><i class="uk-icon-angle-down uk-margin-small-right"></i>' . $element['#title'] . '</a>';
    $output .= '</h3>';
  }

  $content_attribtues = array(
    'id' => $id . '-toggle',
    'class' => array('uk-admin-panel-content-toggle'),
  );

  if ($collapsed) {
    $content_attribtues['class'][] = 'uk-hidden';
    $content_attribtues['aria-hidden'] = 'true';
  }

  $output .= '<div' . drupal_attributes($content_attribtues) . '>';

  if (!empty($element['#description'])) {
    $output .= '<p class="uk-text-muted">' . $element['#description'] . '</p>';
  }

  $output .= $element['#children'];

  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }

  $output .= '</div>';
  $output .= '</div>';
  return $output;
}

/**
 * Implements theme_fieldset().
 */
function uikit_admin_fieldset__non_collapsible($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array());

  $output = '<div' . drupal_attributes($element['#attributes']) . '>';

  if (!empty($element['#title'])) {
    $output .= '<h2>' . $element['#title'] . '</h2>';
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="uk-text-muted">' . $element['#description'] . '</div>';
  }

  $output .= $element['#children'];

  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }

  $output .= '</div>';
  return $output;
}

/**
 * Implements theme_fieldset().
 */
function uikit_admin_fieldset__views_fieldset($variables) {
  $element = $variables['element'];
  $element['#attributes'] = array();
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('form-wrapper'));

  if ($element['#collapsible']) {
    $element['#attributes']['class'][] = 'collapsible';
  }
  if ($element['#collapsed']) {
    $element['#attributes']['class'][] = 'collapsed';
  }
  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
  if (!empty($element['#title'])) {
    // Always wrap fieldset legends in a SPAN for CSS positioning.
    $output .= '<legend><span class="fieldset-legend">' . $element['#title'] . '</span></legend>';
  }
  $output .= '<div class="fieldset-wrapper">';
  if (!empty($element['#description'])) {
    $output .= '<div class="fieldset-description">' . $element['#description'] . '</div>';
  }
  $output .= $element['#children'];
  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }
  $output .= '</div>';
  $output .= "</fieldset>\n";
  return $output;
}

/**
 * Implements theme_filter_tips().
 */
function uikit_admin_filter_tips($variables) {
  $tips = $variables['tips'];
  $long = $variables['long'];
  $output = '';

  $multiple = count($tips) > 1;
  if ($multiple) {
    $output = '<h2>' . t('Text Formats') . '</h2>';
  }

  if (count($tips)) {
    if ($multiple) {
      $output .= '<div class="compose-tips">';
    }

    foreach ($tips as $name => $tiplist) {
      if ($multiple) {
        $output .= '<div class="filter-type filter-' . drupal_html_class($name) . '">';
        $output .= '<h3>' . check_plain($name) . '</h3>';
      }

      if (count($tiplist) > 0) {
        $output .= '<ul class="tips uk-list uk-list-line">';
        foreach ($tiplist as $tip) {
          $output .= '<li' . ($long ? ' id="filter-' . str_replace("/", "-", $tip['id']) . '">' : '>') . $tip['tip'] . '</li>';
        }
        $output .= '</ul>';
      }

      if ($multiple) {
        $output .= '</div><hr class="uk-article-divider">';
      }
    }

    if ($multiple) {
      $output .= '</div>';
    }
  }

  return $output;
}

/**
 * Implements theme_form_element().
 */
function uikit_form_element__views_form_element($variables) {
  $element = &$variables['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="description uk-text-muted">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * Implements theme_form_element_label().
 */
function uikit_admin_form_element_label__item($variables) {
  $element = $variables['element'];
  $title = !empty($element['#title']) ? filter_xss_admin($element['#title']) : '';

  if ($title) {
    return '<h3>' . $title . '</h3>';
  }
}

/**
 * Implements theme_form_element_label() for views form element labels.
 */
function uikit_admin_form_element_label__views_form_element_label($variables) {
  $element = $variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element['#title']);

  $attributes = array();
  // Style the label as class option to display inline with the element.
  if ($element['#title_display'] == 'after') {
    $attributes['class'] = 'option';
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element['#title_display'] == 'invisible') {
    $attributes['class'] = 'element-invisible';
  }

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $t('!title !required', array('!title' => $title, '!required' => $required)) . "</label>\n";
}

/**
 * Implements theme_menu_local_action().
 */
function uikit_admin_menu_local_action($variables) {
  $link = $variables['element']['#link'];
  $output = '<li>';

  if (isset($link['href'])) {
    $output .= l($link['title'], $link['href'], isset($link['localized_options']) ? $link['localized_options'] : array());
  }
  elseif (!empty($link['localized_options']['html'])) {
    $output .= $link['title'];
  }
  else {
    $output .= check_plain($link['title']);
  }

  $output .= '</li>';

  return $output;
}

/**
 * Implements theme_menu_local_task().
 */
function uikit_admin_menu_local_task($variables) {
  $link = $variables['element']['#link'];
  $link_text = $link['title'];

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="uk-hidden">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }

    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }

  return '<li' . (!empty($variables['element']['#active']) ? ' class="active uk-active"' : '') . '>' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n";
}

/**
 * Implements theme_module_filter_operations().
 */
function uikit_admin_module_filter_operations(&$variables) {
  $links = &$variables['links'];
  $dropbutton = $variables['dropbutton'];
  $operations = array();

  foreach (element_children($links) as $key) {
    if ($dropbutton) {
      hide($links[$key]);
      if (!empty($links[$key]['#href'])) {
        $operations[] = array(
          'title' => $links[$key]['#title'],
          'href' => $links[$key]['#href'],
        );
      }
    }
    else {
      $data = drupal_render($links[$key]);
      if (!empty($data)) {
        $operations[] = array('data' => $data);
      }
    }
  }

  if (!empty($operations)) {
    // Define icons for each operation.
    $help_icon = '<i class="uk-icon-question"></i> ';
    $configure_icon = '<i class="uk-icon-cog"></i> ';
    $permissions_icon = '<i class="uk-icon-lock"></i> ';

    foreach ($operations as $key => $operation) {
      // Make sure the links are not passed through check_plain.
      $operations[$key]['html'] = TRUE;

      switch ($operation['title']) {
        // Add the operation's icon to the link title.
        case 'Help':
          $operations[$key]['title'] = $help_icon . $operations[$key]['title'];
          break;

        case 'Configure':
          $operations[$key]['title'] = $configure_icon . $operations[$key]['title'];
          break;

        case 'Permissions':
          $operations[$key]['title'] = $permissions_icon . $operations[$key]['title'];
          break;
      }
    }
    if ($dropbutton) {
      return '<div class="admin-operations">' . theme('links__ctools_dropbutton', array('title' => t('Operations'), 'links' => $operations)) . '</div>';
    }
    return '<div class="admin-operations">' . theme('item_list', array('items' => $operations)) . '</div>';
  }
}

/**
 * Implements theme_node_add_list().
 */
function uikit_admin_node_add_list($variables) {
  $content = $variables['content'];

  if ($content) {
    $output = '<ul class="uk-list uk-list-line uk-admin-list">';

    foreach ($content as $item) {
      $item['localized_options']['attributes']['class'][] = 'uk-text-bold';
      $output .= '<li>';
      $output .= '<i class="uk-icon-chevron-circle-right uk-text-muted uk-display-inline-block uk-admin-vertical-align-top" style="margin-top: 2px"></i>';
      $output .= '<div class="uk-margin-left uk-display-inline-block">';
      $output .= l($item['title'], $item['href'], $item['localized_options']);

      if (isset($item['description'])) {
        $output .= '<div class="uk-text-muted">' . filter_xss_admin($item['description']) . '</div>';
      }

      $output .= '</div>';
      $output .= '</li>';
    }

    $output .= '</ul>';
  }
  else {
    $output .= '<p>' . t('You have not created any content types yet. Go to the <a href="@create-content">content type creation page</a> to add a new content type.', array('@create-content' => url('admin/structure/types/add'))) . '</p>';
  }

  return $output;
}

/**
 * Implements theme_pager().
 */
function uikit_admin_pager($variables) {
  global $pager_page_array;
  global $pager_total;
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];

  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);

  // Current is the page we are currently paged to.
  $pager_current = $pager_page_array[$element] + 1;

  // First is the first page listed by this pager piece (re quantity).
  $pager_first = $pager_current - $pager_middle + 1;

  // Last is the last page listed by this pager piece (re quantity).
  $pager_last = $pager_current + $quantity - $pager_middle;

  // Max is the maximum page number.
  $pager_max = $pager_total[$element];

  // Prepare for generation loop.
  $i = $pager_first;

  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }

  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }

  $li_first = theme('pager_first', array(
    'text' => t('<i class="uk-icon-angle-double-left"></i>'),
    'element' => $element,
    'parameters' => $parameters,
  ));

  $li_previous = theme('pager_previous', array(
    'text' => t('<i class="uk-icon-angle-left"></i>'),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));

  $li_next = theme('pager_next', array(
    'text' => t('<i class="uk-icon-angle-right"></i>'),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));

  $li_last = theme('pager_last', array(
    'text' => t('<i class="uk-icon-angle-double-right"></i>'),
    'element' => $element,
    'parameters' => $parameters,
  ));

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => array('pager-first'),
        'data' => $li_first,
      );
    }

    if ($li_previous) {
      $items[] = array(
        'class' => array('pager-previous'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }

      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_previous', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($pager_current - $i),
              'parameters' => $parameters,
            )),
          );
        }

        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('pager-current', 'uk-active'),
            'data' => '<span>' . $i . '</span>',
          );
        }

        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_next', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($i - $pager_current),
              'parameters' => $parameters,
            )),
          );
        }
      }

      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '<span>…</span>',
        );
      }
    }

    if ($li_next) {
      $items[] = array(
        'class' => array('pager-next'),
        'data' => $li_next,
      );
    }

    if ($li_last) {
      $items[] = array(
        'class' => array('pager-last'),
        'data' => $li_last,
      );
    }

    $pagination = theme('item_list', array(
      'items' => $items,
      'attributes' => array('class' => array('uk-pagination')),
    ));

    return '<h2 class="element-invisible">' . t('Pages') . '</h2>' . $pagination;
  }
}

/**
 * Implements theme_pager_link().
 */
function uikit_admin_pager_link($variables) {
  $text = $variables['text'];
  $page_new = $variables['page_new'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $attributes = $variables['attributes'];
  $page = isset($_GET['page']) ? $_GET['page'] : '';

  if ($new_page = implode(',', pager_load_array($page_new[$element], $element, explode(',', $page)))) {
    $parameters['page'] = $new_page;
  }

  $query = array();

  if (count($parameters)) {
    $query = drupal_get_query_parameters($parameters, array());
  }

  if ($query_pager = pager_get_query_parameters()) {
    $query = array_merge($query, $query_pager);
  }

  // Set each pager link title.
  if (!isset($attributes['title'])) {
    static $titles = NULL;

    if (!isset($titles)) {
      $titles = array(
        t('<i class="uk-icon-angle-double-left"></i>') => t('Go to first page'),
        t('<i class="uk-icon-angle-left"></i>') => t('Go to previous page'),
        t('<i class="uk-icon-angle-right"></i>') => t('Go to next page'),
        t('<i class="uk-icon-angle-double-right"></i>') => t('Go to last page'),
      );
    }

    if (isset($titles[$text])) {
      $attributes['title'] = $titles[$text];
    }
    elseif (is_numeric($text)) {
      $attributes['title'] = t('Go to page @number', array('@number' => $text));
    }
  }

  $attributes['href'] = url($_GET['q'], array('query' => $query));
  return '<a' . drupal_attributes($attributes) . '>' . $text . '</a>';
}

/**
 * Implements theme_status_messages().
 */
function uikit_admin_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );

  foreach (drupal_get_messages($display) as $type => $messages) {
    switch ($type) {
      case 'error':
        $class = 'uk-alert uk-alert-danger';
        break;

      case 'success':
        $class = 'uk-alert uk-alert-success';
        break;

      case 'warning':
        $class = 'uk-alert uk-alert-warning';
        break;

      default:
        $class = 'uk-alert';
    }

    $output .= "<div class='$class' data-uk-alert>";
    $output .= '<a class="uk-alert-close uk-close"></a>';

    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="uk-hidden">' . $status_heading[$type] . "</h2>\n";
    }

    if (count($messages) > 1) {
      $output .= '<ul class="uk-list">';

      foreach ($messages as $message) {
        $output .= '<li>' . $message . '</li>';
      }

      $output .= '</ul>';
    }
    else {
      $output .= reset($messages);
    }

    $output .= '</div>';
  }

  return $output;
}

/**
 * Implements theme_system_compact_link().
 */
function uikit_admin_system_compact_link() {
  $output = '<div class="compact-link uk-width-1-1 uk-margin-small-bottom">';
  if (system_admin_compact_mode()) {
    $output .= l(t('Show descriptions'), 'admin/compact/off', array('attributes' => array('title' => t('Expand layout to include descriptions.')), 'query' => drupal_get_destination()));
  }
  else {
    $output .= l(t('Hide descriptions'), 'admin/compact/on', array('attributes' => array('title' => t('Compress layout by hiding descriptions.')), 'query' => drupal_get_destination()));
  }
  $output .= '</div>';

  return $output;
}

/**
 * Implements theme_system_modules_fieldset().
 */
function uikit_admin_system_modules_fieldset($variables) {
  $form = $variables['form'];
  unset($form['#header'][4]['colspan']);

  // Individual table headers.
  $rows = array();
  // Iterate through all the modules, which are
  // children of this fieldset.
  foreach (element_children($form) as $key) {
    // Stick it into $module for easier accessing.
    $module = $form[$key];
    $row = array();
    unset($module['enable']['#title']);
    $row[] = array('class' => array('checkbox'), 'data' => drupal_render($module['enable']));
    $label = '<label';
    if (isset($module['enable']['#id'])) {
      $label .= ' for="' . $module['enable']['#id'] . '"';
    }
    $row[] = $label . '><strong>' . drupal_render($module['name']) . '</strong></label>';
    $row[] = drupal_render($module['version']);
    // Add the description, along with any modules it requires.
    $description = drupal_render($module['description']);
    if ($module['#requires']) {
      $description .= '<div class="admin-requirements">' . t('Requires: !module-list', array('!module-list' => implode(', ', $module['#requires']))) . '</div>';
    }
    if ($module['#required_by']) {
      $description .= '<div class="admin-requirements">' . t('Required by: !module-list', array('!module-list' => implode(', ', $module['#required_by']))) . '</div>';
    }
    $row[] = array('data' => $description, 'class' => array('description'));

    $links = '';
    $help = isset($module['links']['help']['#href']);
    $permissions = isset($module['links']['permissions']['#href']);
    $configure = isset($module['links']['configure']['#href']);

    if ($help || $permissions || $configure) {
      $links .= '<div class="uk-button-dropdown" data-uk-dropdown="{mode:\'click\'}">';
      $links .= '<div class="uk-admin-system-modules-operations">Operations <i class="uk-icon-caret-down"></i></div>';
      $links .= '<div class="uk-admin-system-modules-operations-dropdown uk-dropdown uk-dropdown-bottom">';
      $links .= '<ul class="uk-nav uk-nav-dropdown">';

      // Display links (such as help or permissions) in a single column.
      foreach (array('help', 'permissions', 'configure') as $link_type) {
        $module['links'][$link_type]['#options']['html'] = TRUE;

        switch ($link_type) {
          case 'help':
            $module['links'][$link_type]['#title'] = '<i class="uk-icon-question"></i> Help';
            break;

          case 'permissions':
            $module['links'][$link_type]['#title'] = '<i class="uk-icon-lock"></i> Permissions';
            break;

          case 'configure':
            $module['links'][$link_type]['#title'] = '<i class="uk-icon-cog"></i> Configure';
            break;
        }

        $links .= '<li class="' . $link_type . '">' . drupal_render($module['links'][$link_type]) . '</li>';
      }

      $links .= '</ul>';
      $links .= '</div>';
      $links .= '</div>';
    }

    $row[] = array('data' => $links, 'class' => array('operations'));

    $rows[] = $row;
  }

  return theme('table', array(
    'header' => $form['#header'],
    'rows' => $rows,
    'attributes' => array(
      'id' => 'system-modules',
    ),
  ));
}

/**
 * Implements theme_table().
 */
function uikit_admin_table__dblog($variables) {
  $header = $variables['header'];
  $rows = $variables['rows'];
  $attributes = $variables['attributes'];
  $caption = $variables['caption'];
  $colgroups = $variables['colgroups'];
  $sticky = $variables['sticky'];
  $empty = $variables['empty'];
  $attributes['class'] = array('uk-table');

  // Add sticky headers, if applicable.
  if (count($header) && $sticky) {
    drupal_add_js('misc/tableheader.js');
    // Add 'sticky-enabled' class to the table to identify it for JS.
    // This is needed to target tables constructed by this function.
    $attributes['class'][] = 'sticky-enabled';
  }

  $output = '<table' . drupal_attributes($attributes) . '>';

  if (isset($caption)) {
    $output .= '<caption>' . $caption . '</caption>';
  }

  // Format the table columns:
  if (count($colgroups)) {
    foreach ($colgroups as $colgroup) {
      $attributes = array();

      // Check if we're dealing with a simple or complex column.
      if (isset($colgroup['data'])) {
        foreach ($colgroup as $key => $value) {
          if ($key == 'data') {
            $cols = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $cols = $colgroup;
      }

      // Build colgroup.
      if (is_array($cols) && count($cols)) {
        $output .= ' <colgroup' . drupal_attributes($attributes) . '>';

        foreach ($cols as $col) {
          $output .= ' <col' . drupal_attributes($col) . ' />';
        }

        $output .= '</colgroup>';
      }
      else {
        $output .= ' <colgroup' . drupal_attributes($attributes) . ' />';
      }
    }
  }

  // Add the 'empty' row message if available.
  if (!count($rows) && $empty) {
    $header_count = 0;

    foreach ($header as $header_cell) {
      if (is_array($header_cell)) {
        $header_count += isset($header_cell['colspan']) ? $header_cell['colspan'] : 1;
      }
      else {
        $header_count++;
      }
    }

    $rows[] = array(
      array(
        'data' => $empty,
        'colspan' => $header_count,
        'class' => array('empty', 'message'),
      ),
    );
  }

  // Format the table header:
  if (count($header)) {
    $ts = tablesort_init($header);
    // HTML requires that the thead tag has tr tags in it followed by tbody
    // tags. Using ternary operator to check and see if we have any rows.
    $output .= (count($rows) ? '<thead><tr class="uk-text-left">' : '<tr>');

    foreach ($header as $cell) {
      $cell = tablesort_header($cell, $header, $ts);
      $output .= _theme_table_cell($cell, TRUE);
    }

    // Using ternary operator to close the tags based on whether or not there
    // are rows.
    $output .= (count($rows) ? '</tr></thead>' : '</tr>');
  }
  else {
    $ts = array();
  }

  // Format the table rows:
  if (count($rows)) {
    $output .= '<tbody>';
    $flip = array('even' => 'odd', 'odd' => 'even');
    $class = 'even';

    foreach ($rows as $row) {
      // Check if we're dealing with a simple or complex row.
      if (isset($row['data'])) {
        $cells = $row['data'];
        $no_striping = isset($row['no_striping']) ? $row['no_striping'] : FALSE;

        // Set the attributes array and exclude 'data' and 'no_striping'.
        $attributes = $row;
        unset($attributes['data']);
        unset($attributes['no_striping']);
      }
      else {
        $cells = $row;
        $attributes = array();
        $no_striping = FALSE;
      }

      if (count($cells)) {
        // Add odd/even class.
        if (!$no_striping) {
          $class = $flip[$class];
          $attributes['class'][] = $class;
        }

        $attributes['class'][] = 'uk-text-left';

        // Get log message severity to add classes to row.
        $info = in_array('dblog-info', $attributes['class']);

        $warning = in_array('dblog-debug', $attributes['class']) ||
          in_array('dblog-warning', $attributes['class']) ||
          in_array('dblog-alert', $attributes['class']);

        $error = in_array('dblog-error', $attributes['class']) ||
          in_array('dblog-critical', $attributes['class']) ||
          in_array('dblog-emerg', $attributes['class']);

        if ($info) {
          $attributes['class'][] = 'uk-alert';
        }
        if ($warning) {
          $attributes['class'][] = 'uk-alert';
          $attributes['class'][] = 'uk-alert-warning';
        }
        if ($error) {
          $attributes['class'][] = 'uk-alert';
          $attributes['class'][] = 'uk-alert-danger';
        }

        // Build row.
        $output .= '<tr' . drupal_attributes($attributes) . '>';
        $i = 0;

        foreach ($cells as $cell) {
          $cell = tablesort_cell($cell, $header, $ts, $i++);

          if ($i == 1) {
            if ($info) {
              $cell = '<i class="uk-icon-info-circle uk-text-primary"></i>';
            }
            if ($warning) {
              $cell = '<i class="uk-icon-exclamation-triangle uk-text-warning"></i>';
            }
            if ($error) {
              $cell = '<i class="uk-icon-exclamation-triangle uk-text-danger"></i>';
            }
          }

          $output .= _theme_table_cell($cell);
        }
        $output .= '</tr>';
      }
    }
    $output .= '</tbody>';
  }

  $output .= '</table>';
  return $output;
}

/**
 * Implements theme_tablesort_indicator().
 */
function uikit_admin_tablesort_indicator($variables) {
  $style = $variables['style'];

  if ($style == 'asc') {
    return '<i class="uk-icon-sort-asc tablesort"></i>';
  }
  else {
    return '<i class="uk-icon-sort-desc tablesort"></i>';
  }
}

/**
 * Implements theme_textfield().
 */
function uikit_admin_textfield__autocomplete($variables) {
  $element = $variables['element'];

  element_set_attributes($element, array(
    'id',
    'name',
    'value',
    'size',
    'maxlength',
  ));

  _form_set_class($element, array('form-text'));
  $element['#attributes']['type'] = 'text';
  $element['#attributes']['size'] = '25';
  $extra = '';

  if ($element['#autocomplete_path'] && !empty($element['#autocomplete_input'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#autocomplete_input']['#id'];
    $attributes['value'] = $element['#autocomplete_input']['#url_value'];
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<i class="uk-icon-spinner"></i>';
    $extra .= '<input' . drupal_attributes($attributes) . ' />';
  }

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $output . $extra;
}

/**
 * Implements theme_update_manager_update_form().
 */
function uikit_admin_update_manager_update_form($variables) {
  $form = drupal_get_form('uikit_admin_form_update_manager_update');
  $last = variable_get('update_last_check', 0);
  $output = theme('update_last_check', array('last' => $last));
  $output .= drupal_render_children($form);
  return $output;
}

/**
 * Form constructor for the overriden update form of the Update Manager module.
 *
 * This presents a table with all projects that have available updates with
 * checkboxes to select which ones to upgrade.
 *
 * @see update_manager_update_form_validate()
 * @see update_manager_update_form_submit()
 * @see uikit_admin_update_manager_update_form()
 */
function uikit_admin_form_update_manager_update($form, $form_state) {
  if (!_update_manager_check_backends($form, 'update')) {
    return $form;
  }

  $form['#theme'] = 'update_manager_update_form';

  $available = update_get_available(TRUE);
  if (empty($available)) {
    $form['message'] = array(
      '#markup' => t('There was a problem getting update information. Try again later.'),
    );
    return $form;
  }

  // This will be a nested array. The first key is the kind of project, which
  // can be either 'enabled', 'disabled', 'manual' (projects which require
  // manual updates, such as core). Then, each subarray is an array of
  // projects of that type, indexed by project short name, and containing an
  // array of data for cells in that project's row in the appropriate table.
  $projects = array();

  // This stores the actual download link we're going to update from for each
  // project in the form, regardless of if it's enabled or disabled.
  $form['project_downloads'] = array('#tree' => TRUE);

  module_load_include('inc', 'update', 'update.compare');
  $project_data = update_calculate_project_data($available);
  foreach ($project_data as $name => $project) {
    // Filter out projects which are up to date already.
    if ($project['status'] == UPDATE_CURRENT) {
      continue;
    }
    // The project name to display can vary based on the info we have.
    if (!empty($project['title'])) {
      if (!empty($project['link'])) {
        $project_name = l($project['title'], $project['link']);
      }
      else {
        $project_name = check_plain($project['title']);
      }
    }
    elseif (!empty($project['info']['name'])) {
      $project_name = check_plain($project['info']['name']);
    }
    else {
      $project_name = check_plain($name);
    }
    if ($project['project_type'] == 'theme' || $project['project_type'] == 'theme-disabled') {
      $project_name .= ' ' . t('(Theme)');
    }

    if (empty($project['recommended'])) {
      // If we don't know what to recommend they upgrade to, we should skip
      // the project entirely.
      continue;
    }

    $recommended_release = $project['releases'][$project['recommended']];
    $recommended_version = $recommended_release['version'] . ' ' . l(t('(Release notes)'), $recommended_release['release_link'], array('attributes' => array('title' => t('Release notes for @project_title', array('@project_title' => $project['title'])))));
    if ($recommended_release['version_major'] != $project['existing_major']) {
      $recommended_version .= '<div title="Major upgrade warning" class="update-major-version-warning">' . t('This update is a major version update which means that it may not be backwards compatible with your currently running version.  It is recommended that you read the release notes and proceed at your own risk.') . '</div>';
    }

    // Create an entry for this project.
    $entry = array(
      'title' => $project_name,
      'installed_version' => $project['existing_version'],
      'recommended_version' => $recommended_version,
    );

    switch ($project['status']) {
      case UPDATE_NOT_SECURE:
      case UPDATE_REVOKED:
        $entry['title'] .= ' ' . t('(Security update)');
        $entry['#weight'] = -2;
        $type = 'security';
        $alert = 'danger';
        break;

      case UPDATE_NOT_SUPPORTED:
        $entry['title'] .= ' ' . t('(Unsupported)');
        $entry['#weight'] = -1;
        $type = 'unsupported';
        $alert = 'warning';
        break;

      case UPDATE_UNKNOWN:
      case UPDATE_NOT_FETCHED:
      case UPDATE_NOT_CHECKED:
      case UPDATE_NOT_CURRENT:
        $type = 'recommended';
        $alert = 'success';
        break;

      case UPDATE_CURRENT:
        $type = 'current';
        $alert = 0;
        break;

      default:
        // Jump out of the switch and onto the next project in foreach.
        continue 2;
    }

    $entry['#attributes'] = array('class' => array('update-' . $type, 'uk-alert'));
    if ($alert) {
      $entry['#attributes']['class'][] = 'uk-alert-' . $alert;
    }

    // Drupal core needs to be upgraded manually.
    $needs_manual = $project['project_type'] == 'core';

    if ($needs_manual) {
      // There are no checkboxes in the 'Manual updates' table so it will be
      // rendered by theme('table'), not theme('tableselect'). Since the data
      // formats are incompatible, we convert now to the format expected by
      // theme('table').
      unset($entry['#weight']);
      $attributes = $entry['#attributes'];
      unset($entry['#attributes']);
      $entry = array(
        'data' => $entry,
      ) + $attributes;
    }
    else {
      $form['project_downloads'][$name] = array(
        '#type' => 'value',
        '#value' => $recommended_release['download_link'],
      );
    }

    // Based on what kind of project this is, save the entry into the
    // appropriate subarray.
    switch ($project['project_type']) {
      case 'core':
        // Core needs manual updates at this time.
        $projects['manual'][$name] = $entry;
        break;

      case 'module':
      case 'theme':
        $projects['enabled'][$name] = $entry;
        break;

      case 'module-disabled':
      case 'theme-disabled':
        $projects['disabled'][$name] = $entry;
        break;
    }
  }

  if (empty($projects)) {
    $form['message'] = array(
      '#markup' => t('All of your projects are up to date.'),
    );
    return $form;
  }

  $headers = array(
    'title' => array(
      'data' => t('Name'),
      'class' => array('update-project-name'),
    ),
    'installed_version' => t('Installed version'),
    'recommended_version' => t('Recommended version'),
  );

  if (!empty($projects['enabled'])) {
    $form['projects'] = array(
      '#type' => 'tableselect',
      '#header' => $headers,
      '#options' => $projects['enabled'],
    );
    if (!empty($projects['disabled'])) {
      $form['projects']['#prefix'] = '<h2>' . t('Enabled') . '</h2>';
    }
  }

  if (!empty($projects['disabled'])) {
    $form['disabled_projects'] = array(
      '#type' => 'tableselect',
      '#header' => $headers,
      '#options' => $projects['disabled'],
      '#weight' => 1,
      '#prefix' => '<h2>' . t('Disabled') . '</h2>',
    );
  }

  // If either table has been printed yet, we need a submit button and to
  // validate the checkboxes.
  if (!empty($projects['enabled']) || !empty($projects['disabled'])) {
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Download these updates'),
    );
    $form['#validate'][] = 'update_manager_update_form_validate';
  }

  if (!empty($projects['manual'])) {
    $prefix = '<h2>' . t('Manual updates required') . '</h2>';
    $prefix .= '<p>' . t('Updates of Drupal core are not supported at this time.') . '</p>';
    $form['manual_updates'] = array(
      '#type' => 'markup',
      '#markup' => theme('table', array('header' => $headers, 'rows' => $projects['manual'])),
      '#prefix' => $prefix,
      '#weight' => 120,
    );
  }

  return $form;
}

/**
 * Implements theme_update_report().
 */
function uikit_admin_update_report($variables) {
  $data = $variables['data'];

  $last = variable_get('update_last_check', 0);
  $output = theme('update_last_check', array('last' => $last));

  if (!is_array($data)) {
    $output .= '<p>' . $data . '</p>';
    return $output;
  }

  $header = array();
  $rows = array();

  // Create an array of status values keyed by module or theme name, since
  // we'll need this while generating the report if we have to cross reference
  // anything (e.g. subthemes which have base themes missing an update).
  foreach ($data as $project) {
    foreach ($project['includes'] as $key => $name) {
      $status[$key] = $project['status'];
    }
  }

  foreach ($data as $project) {
    switch ($project['status']) {
      case UPDATE_CURRENT:
        $class = 'success';
        $icon = 'check';
        break;

      case UPDATE_UNKNOWN:
      case UPDATE_FETCH_PENDING:
      case UPDATE_NOT_FETCHED:
        $class = 'warning';
        $icon = 'question-circle';
        break;

      case UPDATE_NOT_SECURE:
      case UPDATE_REVOKED:
      case UPDATE_NOT_SUPPORTED:
        $class = 'danger';
        $icon = 'exclamation-circle';
        break;

      case UPDATE_NOT_CHECKED:
      case UPDATE_NOT_CURRENT:
      default:
        $class = 'warning';
        $icon = 'exclamation-triangle';
        break;
    }

    $row = '<div class="version-status uk-float-right">';
    $status_label = theme('update_status_label', array('status' => $project['status']));
    $row .= !empty($status_label) ? $status_label : check_plain($project['reason']);
    $row .= '<i class="uk-icon-' . $icon . ' uk-text-' . $class . '"></i>';
    $row .= '</div>';

    $row .= '<div class="project uk-text-bold uk-admin-text-dark">';
    if (isset($project['title'])) {
      if (isset($project['link'])) {
        $row .= l($project['title'], $project['link']);
      }
      else {
        $row .= check_plain($project['title']);
      }
    }
    else {
      $row .= check_plain($project['name']);
    }
    $row .= ' ' . check_plain($project['existing_version']);
    if ($project['install_type'] == 'dev' && !empty($project['datestamp'])) {
      $row .= ' <span class="version-date">(' . format_date($project['datestamp'], 'custom', 'F j, Y') . ')</span>';
    }
    $row .= '</div>';

    $versions_inner = '';
    $security_class = array();
    $version_class = array();
    if (isset($project['recommended'])) {
      if ($project['status'] != UPDATE_CURRENT || $project['existing_version'] !== $project['recommended']) {

        // First, figure out what to recommend.
        // If there's only 1 security update and it has the same version we're
        // recommending, give it the same CSS class as if it was recommended,
        // but don't print out a separate "Recommended" line for this project.
        if (!empty($project['security updates']) && count($project['security updates']) == 1 && $project['security updates'][0]['version'] === $project['recommended']) {
          $security_class[] = 'version-recommended';
          $security_class[] = 'version-recommended-strong';
          $security_class[] = 'uk-text-bold';
        }
        else {
          $version_class[] = 'version-recommended';
          // Apply an extra class if we're displaying both a recommended
          // version and anything else for an extra visual hint.
          if ($project['recommended'] !== $project['latest_version']
            || !empty($project['also'])
            || ($project['install_type'] == 'dev'
              && isset($project['dev_version'])
              && $project['latest_version'] !== $project['dev_version']
              && $project['recommended'] !== $project['dev_version'])
            || (isset($project['security updates'][0])
              && $project['recommended'] !== $project['security updates'][0])
          ) {
            $version_class[] = 'version-recommended-strong';
            $version_class[] = 'uk-text-bold';
          }
          $version_class[] = 'uk-clearfix';
          $versions_inner .= theme('update_version', array(
            'version' => $project['releases'][$project['recommended']],
            'tag' => t('Recommended version:'),
            'class' => $version_class,
          ));
        }

        // Now, print any security updates.
        if (!empty($project['security updates'])) {
          $security_class[] = 'version-security';
          $security_class[] = 'uk-clearfix';
          foreach ($project['security updates'] as $security_update) {
            $versions_inner .= theme('update_version', array(
              'version' => $security_update,
              'tag' => t('Security update:'),
              'class' => $security_class,
            ));
          }
        }
      }

      if ($project['recommended'] !== $project['latest_version']) {
        $versions_inner .= theme('update_version', array(
          'version' => $project['releases'][$project['latest_version']],
          'tag' => t('Latest version:'),
          'class' => array('version-latest', 'uk-clearfix'),
        ));
      }
      if ($project['install_type'] == 'dev'
        && $project['status'] != UPDATE_CURRENT
        && isset($project['dev_version'])
        && $project['recommended'] !== $project['dev_version']) {
        $versions_inner .= theme('update_version', array(
          'version' => $project['releases'][$project['dev_version']],
          'tag' => t('Development version:'),
          'class' => array('version-latest', 'uk-clearfix'),
        ));
      }
    }

    if (isset($project['also'])) {
      foreach ($project['also'] as $also) {
        $versions_inner .= theme('update_version', array(
          'version' => $project['releases'][$also],
          'tag' => t('Also available:'),
          'class' => array('version-also-available'),
        ));
      }
    }

    if (!empty($versions_inner)) {
      $row .= '<div class="versions">' . $versions_inner . '</div>';
    }
    $row .= '<div class="info">';
    if (!empty($project['extra'])) {
      $row .= '<div class="extra">';
      foreach ($project['extra'] as $key => $value) {
        $row .= '<div class="' . implode(' ', $value['class']) . '">';
        $row .= check_plain($value['label']) . ': ';
        $row .= drupal_placeholder($value['data']);
        $row .= '</div>';
      }
      $row .= '</div>';
    }

    $row .= '<div class="includes">';
    sort($project['includes']);
    if (!empty($project['disabled'])) {
      sort($project['disabled']);
      // Make sure we start with a clean slate for each project in the report.
      $includes_items = array();
      $row .= t('<strong>Includes: </strong>');
      $includes_items[] = t('Enabled: %includes', array('%includes' => implode(', ', $project['includes'])));
      $includes_items[] = t('Disabled: %disabled', array('%disabled' => implode(', ', $project['disabled'])));
      $row .= theme('item_list', array('items' => $includes_items));
    }
    else {
      $includes = t('<strong>Includes: </strong>%includes', array('%includes' => implode(', ', $project['includes'])));
      $includes = str_replace('class="placeholder"', 'class="placeholder uk-text-' . $class . '"', $includes);
      $row .= $includes;
    }
    $row .= '</div>';

    if (!empty($project['base_themes'])) {
      $row .= '<div class="basethemes">';
      asort($project['base_themes']);
      $base_themes = array();
      foreach ($project['base_themes'] as $base_key => $base_theme) {
        switch ($status[$base_key]) {
          case UPDATE_NOT_SECURE:
          case UPDATE_REVOKED:
          case UPDATE_NOT_SUPPORTED:
            $base_themes[] = t('%base_theme (!base_label)', array(
              '%base_theme' => $base_theme,
              '!base_label' => theme('update_status_label', array(
                'status' => $status[$base_key],
              )),
            ));
            break;

          default:
            $base_themes[] = drupal_placeholder($base_theme);
        }
      }
      $row .= t('Depends on: !basethemes', array('!basethemes' => implode(', ', $base_themes)));
      $row .= '</div>';
    }

    if (!empty($project['sub_themes'])) {
      $row .= '<div class="subthemes">';
      sort($project['sub_themes']);
      $row .= t('Required by: %subthemes', array('%subthemes' => implode(', ', $project['sub_themes'])));
      $row .= '</div>';
    }

    $row .= '</div>';

    if (!isset($rows[$project['project_type']])) {
      $rows[$project['project_type']] = array();
    }
    $row_key = isset($project['title']) ? drupal_strtolower($project['title']) : drupal_strtolower($project['name']);
    $rows[$project['project_type']][$row_key] = array(
      'class' => array('uk-alert', 'uk-alert-' . $class),
      'data' => array($row),
    );
  }

  $project_types = array(
    'core' => t('Drupal core'),
    'module' => t('Modules'),
    'theme' => t('Themes'),
    'module-disabled' => t('Disabled modules'),
    'theme-disabled' => t('Disabled themes'),
  );
  foreach ($project_types as $type_name => $type_label) {
    if (!empty($rows[$type_name])) {
      ksort($rows[$type_name]);
      $output .= '<h3 class="uk-text-bold">' . $type_label . '</h3>';
      $output .= theme('table', array(
        'header' => $header,
        'rows' => $rows[$type_name],
        'attributes' => array('class' => array('update')),
      ));
    }
  }
  return $output;
}

/**
 * Implements theme_update_status_label().
 */
function uikit_admin_update_status_label($variables) {
  switch ($variables['status']) {
    case UPDATE_NOT_SECURE:
      return '<span class="uk-margin-right">' . t('Security update required!') . '</span>';

    case UPDATE_REVOKED:
      return '<span class="uk-margin-right">' . t('Revoked!') . '</span>';

    case UPDATE_NOT_SUPPORTED:
      return '<span class="uk-margin-right">' . t('Not supported!') . '</span>';

    case UPDATE_NOT_CURRENT:
      return '<span class="uk-margin-right">' . t('Update available') . '</span>';

    case UPDATE_CURRENT:
      return '<span class="uk-margin-right">' . t('Up to date') . '</span>';

  }
}

/**
 * Implements theme_update_version().
 */
function uikit_admin_update_version($variables) {
  $version = $variables['version'];
  $tag = $variables['tag'];
  $class = implode(' ', $variables['class']);

  $output = '';
  $output .= '<div class="version ' . $class . '">';
  $output .= '<div class="version-title uk-display-inline-block"><strong>' . $tag . '</strong></div>';
  $output .= '<div class="version-details uk-display-inline-block uk-margin-left">';
  $output .= l($version['version'], $version['release_link']);
  $output .= ' <span class="version-date">(' . format_date($version['date'], 'custom', 'F j, Y') . ')</span>';
  $output .= '</div>';
  $output .= '<div class="version-links uk-float-right">';
  $links = array();
  $links['update-download'] = array(
    'title' => t('Download'),
    'href' => $version['download_link'],
  );
  $links['update-release-notes'] = array(
    'title' => t('Release notes'),
    'href' => $version['release_link'],
  );
  $attributes = array(
    'class' => array('uk-list uk-margin-right uk-margin-bottom-remove uk-text-center'),
  );
  $output .= theme('links__update_version', array('links' => $links, 'attributes' => $attributes));
  $output .= '</div>';
  $output .= '</div>';
  return $output;
}
