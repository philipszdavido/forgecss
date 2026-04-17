#  CSS Parser
```css
body {
  color: red;
  margin: 10px;
}

h1, h2 {
  font-size: 20px;
}
```

```json
{
  type: "Stylesheet",
  rules: [
    {
      type: "Rule",
      selectors: ["body"],
      declarations: [
        { property: "color", value: "red" },
        { property: "margin", value: "10px" }
      ]
    },
    {
      type: "Rule",
      selectors: ["h1", "h2"],
      declarations: [
        { property: "font-size", value: "20px" }
      ]
    }
  ]
}
```

.baseline-status[data-astro-cid-7wt35nye]::part(root)

{
  type: "Selector",
  parts: [
    { type: "ClassSelector", name: "baseline-status" },
    {
      type: "AttributeSelector",
      name: "data-astro-cid-7wt35nye",
      operator: null,
      value: null
    },
    {
      type: "PseudoElement",
      name: "part",
      argument: "root"
    }
  ]
}

--color-outline--light: #d9d9d9;

{
  type: "Declaration",
  property: "--color-outline--light",
  value: {
    type: "Color",
    format: "hex",
    value: "#d9d9d9"
  }
}

border: 1px solid var(--color-outline);

{
  type: "Declaration",
  property: "border",
  value: [
    { type: "Dimension", value: 1, unit: "px" },
    { type: "Keyword", value: "solid" },
    {
      type: "Function",
      name: "var",
      args: ["--color-outline"]
    }
  ]
}


